#pragma once
#include <time.h>
#include <chrono>
#include <thread>
#include "GrahamScan.h"
class visualConvexHull {
private:
	grahamScan h_graham;//holds the parent like class 
	std::stack<Point> h_visualStack;//used to hold the visual stack of 
							//points that are drawn as they are stacked.
	std::vector<Point> h_redDots;//hold the failed points that didn't
							//pass the counterclockwise test.

	int waitSeconds; //the delay in miliseconds each time something is drawn

	//private functions
	bool VisualStack(int count); //makes the stack for visualConvexHull also draw the point being compared in it blue
	//handles if a point is pushed to h_redDots if the point fails the counterclockwise test
	void DrawRedLine(Point p1, Point p2);//draws a red line to signify checking points.
	void DrawGreenLine(Point p1, Point p2);//draws a green line between two points
	Point NextToTop();//gets the point under h_visualStack.top

public:
	//Constructors
	visualConvexHull();
	visualConvexHull(std::vector<Point> points);

	//public functions

	void visualConvexHullRun();//the run function
    void playSound();
};