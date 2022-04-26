#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/freetype.hpp>
#include <iostream>

//using namespace cv;

//Stores the values of an image
inline cv::Mat img, img_threshold, img_gray, img_roi, process;

//run loop
void runCameraHull();

//Process the image from the webcam
cv::Mat processingImg(cv::Mat img);

//Gets the contours
std::vector<cv::Point> getContours(cv::Mat img);
