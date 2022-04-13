#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <math.h>			//also for M_PI
#include "GrahamScan.h"


//constructors
grahamScan::grahamScan() {
	std::vector<Point> points;
	this->m_Points = points;
}

grahamScan::grahamScan(std::vector<Point> points) {
	this->m_Points = points;
}

//private functions
//void grahamScan::SortPoints() {
//	if (!m_Points.empty()) {
//		int min = 0;	//index for the min value
//		for (int x = 0; x < this->m_Points.size(); x++) {
//			if (m_Points[x].x < m_Points[min].x ||		//if it finds a point with the x cord less than min
//				(m_Points[x].x == m_Points[min].x &&	//or it finds a point with the x cord = and the y-cord less
//					m_Points[x].y < m_Points[min].y)) { //overwrite min
//				min = x;
//			}
//		}
//	}

double grahamScan::CalcAnglePolar(Point vertex, Point p1, Point p2) {

	//uses the Law of Cosines in order to get the angle of the three points

	double ret; //the angle that will be returned

	//baking some pi
	double pi;
	pi = atan(1) * 4;

	//the calculation of the length of the first line between vertex and p1
	double lineseglength1 = sqrt(abs(pow((vertex.x - p1.x), 2) + pow((vertex.y - p1.y), 2)));
	//second line between vertex and p2
	double lineseglength2 = sqrt(abs(pow((vertex.x - p2.x), 2) + pow((vertex.y - p2.y), 2)));
	//vertex and p3
	double lineseglength3 = sqrt(abs(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)));
	
	//calculates the angle in radian form using law of cosines
	ret = acos(abs((pow(lineseglength1, 2) + pow(lineseglength2, 2) - pow(lineseglength3, 2)) / (2 * lineseglength1 * lineseglength2)));
	
	//converts the return value to degrees
	ret *= 180;
	ret = ret / pi;

	return ret;

}

void grahamScan::AssignPolarAngle() {
	//this is used to assagin each point in m_Points an angle defined from the bottommost point
	//and the x axis. It won't assign anything to the first point becasue it should be
	//Null as it's used as the vertex.
	//the First point has to be the bottom most point

	//defines an int so .size() isn't repeatedly called
	int vecLength = this->m_Points.size();

	//uses CalcAngle against the first point in the Points vector to calculate and assign an angle
	for (int x = 1; x < vecLength; x++) {
		Point xAxis = Point(this->m_Points[x].x, this->m_Points[0].y);
		this->m_Points[x].polar_angle = CalcAnglePolar(this->m_Points[0], this->m_Points[x], xAxis);
	}
}

void grahamScan::SortPoints() {
	//this will give each point an angle 
	AssignPolarAngle();
	//this sorts the vector base on polar Angle 
	std::sort(this->m_Points.begin(), this->m_Points.end(),
		[](auto& prev, auto& next) {
			return prev.polar_angle < next.polar_angle;
		});
}

void grahamScan::GrahamStack() {
	//should only be run if there are more than 3 points
	
	SortPoints();
	int pointSize = m_Points.size();
	for (int i = 0; i < pointSize; i++) {
		
		Point top = this->m_Stack.top(); 
		//used to hold the top part of the stack so
		//we can get the value next to the top of the stack as well
		m_Stack.pop();

		Point top_next = this->m_Stack.top();

		this->m_Stack.push(top_next);
		this->m_Stack.push(top);

		while (m_Stack.size() > 1 &&
			ClockwiseTurn(top_next, top, this->m_Points[i])>0) 
			//while the top of the stack has to turn clockwise to look at the next point
			//pop the point from the stack and compare the next top of the stack
		{
			//pop the stack
			m_Stack.pop();
		}
		m_Stack.push(m_Points[i]);
	}
}

double grahamScan::ClockwiseTurn(Point vertex, Point p1, Point p2) {
	//Will return postive number if the point turns clockwise
	//when used for grahm scan the points should be pased in as
	//(next_to_top(Stack), top(stack), Point) 

	//uses the Law of Cosines in order to get the angle of the three points

	double ret; //the angle that will be returned

	//baking some pie
	double pi;
	pi = atan(1) * 4;

	//uses dot product then modifies in order to see if the point turns clockwise or counter clockwise to look at the next point. 
	ret = (atan2(p2.y - vertex.y, p2.x - vertex.x) -
		atan2(p1.y - vertex.y, p1.x - vertex.x));
	//converts the return value to degrees
	ret *= 180;
	ret = ret / pi;

	//if the angle is more than 180 it turns counter clockwise. 
	if (ret >= 180) {
		ret *= -1;
	}

	return ret;

}

Point grahamScan::NextToTop(std::stack<Point> stack) {
	//used to get the point next to the top of the stack
	//mostly used to make the code look cleaner and make i
	//easier to read at func GrahamStack().

	Point Temp; 
	stack.pop();
	Temp = stack.top();

	return Temp;
}

	//TBD!!!!!

	//the next part needs a way to compare a point with the P0 (the min
	//Point that was found above) and the x axis, to find the angle 
	//those points make and then sort the Points based on the angle they made.
	//supposedly we don't need to compute the angle becasue we could use
	//the dot product or some math-angle-magic stuff. Ima leave that up to
	//Lemmy becasue he's the best at math lol. 
//}