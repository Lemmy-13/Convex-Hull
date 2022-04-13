//This class is used for the Graham's scan calculations used to compute Convex Hull
#pragma once
#include "Point.h"
#include "ch.h"
#include <vector>
#include <stack>


//TBD
//Make Run func that holds the while window while loop
//make window data point
//make a draw line func onto window
//add clock stuff
class grahamScan {
private:
	std::vector<Point> m_Points;		//used to store all points that the users inputs by clicking in the window
	std::stack<Point> m_Stack;		//used to stack the points in order for Convex Hull. 

	//private functions
	//float CounterClockWise(Point, Point, Point);	//this function will take three points and tell if the angle made by the points
												//is clockwise. If the function returns > 0 it's Counter clockwise. < Clockwise. = 0  Colinear
	void AssignPolarAngle();	//uses the vector of points to assign the polar angle to the points with the vector having to be in order
								//with m_points[0] being the bottomost point. 
	void SortPoints();	//used to sort m_Points in order from the angle that point P0(point with the smallest x) and
						//the next points, make with the x-axis. This function is private because it should be called by
						//another function later.
	double CalcAnglePolar(Point vertex, Point p1, Point p2); //return the angle of 3 points in degrees
	void GrahamStack(); //used to make the stack using grahamScan's formula

	double ClockwiseTurn(Point vertex, Point p1, Point p2); //will return >= 0 if clockwise. 

	Point NextToTop(std::stack<Point> stack); //used to get the point next to the top of the stack
public:
	//Constructors
	grahamScan();
	grahamScan(std::vector<Point> points);

	//functions
};