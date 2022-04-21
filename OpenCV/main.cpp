#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;

//Stores the values of an image
Mat img, img_threshold, img_gray, img_roi, process;

//Process the image from the webcam
Mat processingImg(Mat img)
{
    // Drawing the rectangle on the screen
    Rect roi(10, 20, 310, 310);

    //Passing the roi to the image
    img_roi = img(roi);

    //Converts the image to a different color
    cvtColor(img_roi,img_gray, COLOR_RGB2GRAY);

    //Blurring the image from the webcam
    GaussianBlur(img_gray,img_gray,Size(19, 19),0, 0);

    //Getting the threshold for the image
    threshold(img_gray,img_threshold,0,255,THRESH_BINARY_INV + THRESH_OTSU);

    return process;
}

//Gets the contours
vector<Point> getContours(Mat image) 
{
    //Save the numbers
    char numbersf[40];
    //Counter for the fingers
    int count = 0;

    vector<vector<Point> >contours;
    vector<Vec4i>hierarchy;

    findContours(img_threshold,contours,hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

    vector<Point> biggest;
    vector<vector<int> >hull(contours.size());
    vector<vector<Point> >hullPoint(contours.size());
    vector<vector<Vec4i> >defects(contours.size());
    vector<vector<Point> >defectPoint(contours.size());
    vector<vector<Point> >contours_poly(contours.size());
    Point2f rect_point[4];
    vector<RotatedRect>minRect(contours.size());
    vector<Rect> boundRect(contours.size());

    if(contours.size()>0)
    {
        size_t indexOfBiggestContour = -1;
	    size_t sizeOfBiggestContour = 0;

	    for (size_t i = 0; i < contours.size(); i++)
        {
		    if(contours[i].size() > sizeOfBiggestContour)
            {
			    sizeOfBiggestContour = contours[i].size();
			    indexOfBiggestContour = i;
		    }
        }

        for(size_t i = 0; i < contours.size(); i++)
        {
            if(contourArea(contours[i]) > 5000)
            {
                convexHull(contours[i],hull[i],true);
                convexityDefects(contours[i],hull[i],defects[i]);
                if(indexOfBiggestContour==i)
                {
                    minRect[i]=minAreaRect(contours[i]);
                    for(size_t k=0;k<hull[i].size();k++)
                    {
                        int ind=hull[i][k];
                        hullPoint[i].push_back(contours[i][ind]);
                    }
                    count =0;

                    for(size_t k=0;k<defects[i].size();k++)
                    {
                        if(defects[i][k][3]>13*256)
                        {
                            /*   int p_start=defects[i][k][0];   */
                            int p_end=defects[i][k][1];
                            int p_far=defects[i][k][2];
                            defectPoint[i].push_back(contours[i][p_far]);
                            circle(img_roi,contours[i][p_end],3,Scalar(0,255,0),2);
                            count++;
                        }

                    }

                    if(count==1)
                        strcpy(numbersf,"1");
                    else if(count==2)
                        strcpy(numbersf,"2");
                    else if(count==3)
                            strcpy(numbersf,"3");
                    else if(count==4)
                            strcpy(numbersf,"4");
                    else if(count==5)
                            strcpy(numbersf,"5");
                    else
                            strcpy(numbersf,"0");

                    putText(img,numbersf,Point(70,70), FONT_HERSHEY_TRIPLEX,4,Scalar(0, 128, 0),3,8,false);
                    drawContours(img_threshold, contours, i,Scalar(255,255,0),2, 8, vector<Vec4i>(), 0, Point() );
                    drawContours(img_threshold, hullPoint, i, Scalar(255,255,0),1, 8, vector<Vec4i>(),0, Point());
                    drawContours(img_roi, hullPoint, i, Scalar(0,0,255),2, 8, vector<Vec4i>(),0, Point() );
                    approxPolyDP(contours[i],contours_poly[i],3,false);
                    boundRect[i]=boundingRect(contours_poly[i]);
                    rectangle(img_roi,boundRect[i].tl(),boundRect[i].br(),Scalar(255,0,0),2,8,0);
                    minRect[i].points(rect_point);

                    for(size_t k=0;k<4;k++)
                    {
                        line(img_roi,rect_point[k],rect_point[(k+1)%4],Scalar(0,255,0),2,8);
                    }

                }
            }
              
        }
    }
    return biggest;
}

int main( int argc, const char** argv)
{

    //Load webcam
    VideoCapture cam(0);
    //Webcam settings
    cam.set(CAP_PROP_SETTINGS, 1);

    while(true)
    {

        //Check image from the webcam
        bool b=cam.read(img);
        if(!b)
        {
            cout << "ERROR : cannot read" << endl;
            return -1;
        }

        processingImg(img);
        getContours(img);

        imshow("Convex Hull",img);
        imshow("Calibration",img_threshold);

        if(waitKey(30)==27)
        {
            return -1;
        }
    }
}