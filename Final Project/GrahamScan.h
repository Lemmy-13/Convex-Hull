//This class is used for the Graham's scan calculations used to compute Convex Hull
#pragma once
#include "Point.h"
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>
#include <fstream>			
#include <math.h>			
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class grahamScan {
private:
	std::vector<Point> m_Points;		//used to store all points that the users inputs by clicking in the window
	std::stack<Point> m_Stack;			//used to stack the points in order for Convex Hull. 
	sf::RenderWindow *m_window;			//used for the window
	int m_WindowWidth;					//used for the width of the window
	int m_WindowHeight;					//used for the height of the window

	//private functions
	void AssignPolarAngle();	//uses the vector of points to assign the polar angle to the points with the vector having to be in order
								//with m_points[0] being the bottomost point. 
	void SortPoints();	//used to sort m_Points in order from the angle that point P0(point with the smallest x) and
						//the next points, make with the x-axis. This function is private because it should be called by
						//another function later.
	double CalcAnglePolar(Point vertex, Point p1, Point p2); //return the angle of 3 points in degrees
	void GrahamStack(); //used to make the stack using grahamScan's formula

	double ClockwiseTurn(Point vertex, Point p1, Point p2); //will return >= 0 if clockwise. 

	Point NextToTop(); //used to get the point next to the top of the stack
	void initWindow(); //used to set up the window thing utilizing a config ini

	void DrawLine(Point p1, Point p2); //used to draw a blue line between two points
	void BottomMost(int x, int y);	//used to compare if the x and y are lower than m_points[0]
public:
	//Constructors
	grahamScan();
	grahamScan(std::vector<Point> points);

	//run functions
	void RunStandardHull(); //used for running the standard click points and compute setup.

	friend class visualConvexHull;
};

