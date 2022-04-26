#include "Finger.h"

//Process the image from the webcam
cv::Mat processingImg(cv::Mat img)
{
    // Drawing the rectangle on the screen
    cv::Rect roi(10, 20, 310, 310);

    //Passing the roi to the image
    img_roi = img(roi);

    //Converts the image to a different color
    cvtColor(img_roi,img_gray, cv::COLOR_RGB2GRAY);

    //Blurring the image from the webcam
    GaussianBlur(img_gray,img_gray,cv::Size(19, 19),0, 0);

    //Getting the threshold for the image
    threshold(img_gray,img_threshold,0,215,cv::THRESH_BINARY_INV + cv::THRESH_OTSU);

    return process;
}

void runCameraHull(){

    //Load webcam
    cv::VideoCapture cam(0);
    //Webcam settings
    cam.set(cv::CAP_PROP_SETTINGS, 1);

    while(true)
    {

        //Check image from the webcam
        bool b=cam.read(img);
        if(!b)
        {
            std::cout << "ERROR : cannot read" << std::endl;
            cv::destroyAllWindows();
            break;
        }

        //Functions
        processingImg(img);
        getContours(img);

        //Show
        imshow("Finger Count",img);
        imshow("Calibration",img_threshold);

        if(cv::waitKey(30)==27)
        {
            cv::destroyAllWindows();
            break;
        }
    }

}
//Gets the contours
std::vector<cv::Point> getContours(cv::Mat img)
{
    //Save the numbers
    char numbersf[40];
    //Counter for the fingers
    int count = 0;

    std::vector<std::vector<cv::Point> >contours;
    std::vector<cv::Vec4i>hierarchy;

    findContours(img_threshold,contours,hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE, cv::Point());

    std::vector<cv::Point> biggest;
    std::vector<std::vector<int> >hull(contours.size());
    std::vector<std::vector<cv::Point> >hullPoint(contours.size());
    std::vector<std::vector<cv::Vec4i> >defects(contours.size());
    std::vector<std::vector<cv::Point> >defectPoint(contours.size());
    std::vector<std::vector<cv::Point> >contours_poly(contours.size());
    cv::Point2f rect_point[4];
    std::vector<cv::RotatedRect>minRect(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

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

                    for(size_t k = 0; k < defects[i].size(); k++)
                    {
                        if(defects[i][k][3]>13*256)
                        {
                            int p_end=defects[i][k][1];
                            int p_far=defects[i][k][2];
                            defectPoint[i].push_back(contours[i][p_far]);
                            circle(img_roi,contours[i][p_end],3, cv::Scalar(0,255,0),2);
                            count++;
                        }
                    }

                    //Check the numbers
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

                    //Display numbers
                    cv::Ptr<cv::freetype::FreeType2> ft2;
                    ft2 = cv::freetype::createFreeType2();
                    ft2->loadFontData( "/Users/lemmy/Documents/Projects/Menu/FSEX300.ttf", 0 );
                    ft2->putText(img,numbersf,cv::Point(70,600), 100,cv::Scalar(0,255,0),3,8,false);

                    approxPolyDP(contours[i],contours_poly[i],3,false);
                    boundRect[i]=boundingRect(contours_poly[i]);
                    minRect[i].points(rect_point);

                    for(size_t k=0;k<4;k++)
                    {
                        line(img_roi,rect_point[k],rect_point[(k+1)%4], cv::Scalar(0,255,255),5,8);
                    }

                }
            }

        }
    }
    return biggest;
}