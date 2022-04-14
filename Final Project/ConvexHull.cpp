#include <iostream>
#include "GrahamScan.h"


//constructors
grahamScan::grahamScan() {
	std::vector<Point> points;
	std::stack<Point> stack;
	this->m_Points = points;
	this->m_Stack = stack;
	this->initWindow();
}

grahamScan::grahamScan(std::vector<Point> points) {
	this->m_Points = points;
}

//private functions shouldn't needed to be used outside this class.
void grahamScan::initWindow() {

	//creates window using window.ini file

	std::ifstream ifs("Config/window.ini");

	std::string title = "ConvexHull Window";
	sf::VideoMode window_bounds(800, 600);
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;


	//We should use a gui to help set these up with the ini
	//but this should work for now. 
	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;

	}
	this->m_window = new sf::RenderWindow(window_bounds, title);
	this->m_window->setFramerateLimit(framerate_limit);
	this->m_window->setVerticalSyncEnabled(vertical_sync_enabled);
	this-> m_WindowWidth = window_bounds.width;
	this->m_WindowHeight = window_bounds.height;

}

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

void grahamScan::DrawLine(Point p1, Point p2) {

	//used to draw a blue line between two points
	sf::VertexArray line(sf::Lines, 2);

	//setting pos
	line[0].position = sf::Vector2f(p1.x, p1.y);
	line[1].position = sf::Vector2f(p2.x, p2.y);

	//setting color
	line[0].color = sf::Color::Blue;
	line[1].color = sf::Color::Blue;

	//drawing it to the grahmScan object window. 
	this->m_window->draw(line);

}

void grahamScan::BottomMost(int x, int y) {
	Point point = Point(x, y);
	if (!this->m_Points.empty()) {
		if ((point.y) > (this->m_Points[0].y)) {
			this->m_Points.push_back(this->m_Points[0]);
			this->m_Points[0] = point; 
		}
		/*else if (point.y == this->m_Points[0].y &&
			point.x < m_Points[0].x) {
			this->m_Points.push_back(this->m_Points[0]);
			this->m_Points[0] = point;
		}*/
		else {
			this->m_Points.push_back(point);
		}
	}
	else {
		this->m_Points.push_back(point);
	}
}


//The Run functions for the differnt types of ConvexHull we are building
void grahamScan::RunStandardHull() {
	while (this->m_window->isOpen()) {
		//Process events
		sf::Event event;
		while (this->m_window->pollEvent(event)) 
		{
			//Close window if they click exit.
			if (event.type == sf::Event::Closed) {
				this->m_window->close();
			}
			
			//button presses
			
			if (event.type == sf::Event::MouseButtonPressed) 
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//Point temp(event.mouseButton.x, event.mouseButton.y);
					this->BottomMost(event.mouseButton.x, event.mouseButton.y);//pushes back the Point or reassigns to the front if it's the bottomost point
					//this->m_Points.push_back(temp);
				}
			}
		}

		this->m_window->clear();

		for (int i = 0; i < this->m_Points.size(); i++) {
			sf::CircleShape whitedot(3);
			whitedot.setPosition(this->m_Points[i].x, this->m_Points[i].y);
			std::cout << i <<" "<< this->m_Points[i].x << " " << this->m_Points[i].y << std::endl;
			this->m_window->draw(whitedot);
		}

		this->m_window->display();

	}

}

	//TBD!!!!!

	//the next part needs a way to compare a point with the P0 (the min
	//Point that was found above) and the x axis, to find the angle 
	//those points make and then sort the Points based on the angle they made.
	//supposedly we don't need to compute the angle becasue we could use
	//the dot product or some math-angle-magic stuff. Ima leave that up to
	//Lemmy becasue he's the best at math lol. 
//}