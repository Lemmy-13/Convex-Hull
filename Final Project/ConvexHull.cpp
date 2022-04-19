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

	double ret; //the angle that will be returned

	//baking some pi
	double pi;
	pi = atan(1) * 4;

	//this will gets the angle based on the x axis and goes clockwise to the point in order to get the angle.
	double compareX = p1.x;
	double compareY = vertex.y;

	compareX -= vertex.x;
	compareY -= p1.y;

	ret = atan2(compareY, compareX);

	if (ret < 0) {
		ret = std::abs(ret);
	}
	else {
		ret = 2 * pi - ret;
	}
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

	//sets point [0] polar angle to null in case of previous calls
	this->m_Points[0].polar_angle = NULL;
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
	std::sort(this->m_Points.begin()+1, this->m_Points.end(),
		[](auto& prev, auto& next) {
			if (prev.polar_angle == next.polar_angle) {
				//really dumb workaround for the sort breaking if the 
				//polar angles are the equal
				prev.polar_angle += .0000001;
			}
			return prev.polar_angle >= next.polar_angle;
		});
}

void grahamScan::GrahamStack() {
	//should only be run if there are more than 3 points
	this->m_Stack = std::stack<Point>();
	this->SortPoints();
	int pointSize = m_Points.size();

	//cylces through the points in the list.
	for (int i = 0; i < pointSize; i++) {
		while (m_Stack.size() > 1 &&
			this->ClockwiseTurn(this->m_Stack.top(), this->NextToTop(), this->m_Points[i]) >= 0)
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

	double ret; //the angle that will be returned

	//baking some pie
	double pi;
	pi = atan(1) * 4;

	//uses dot product then modifies in order to see if the point turns clockwise or counter clockwise to look at the next point. 
	

	double abvecX = p1.x - vertex.x;
	double abvecY = p1.y - vertex.y;

	double bcvecX = vertex.x - p2.x;
	double bcvecY = vertex.y - p2.y;

	double dotproduct = (abvecX * bcvecX) + (abvecY * bcvecY);

	double determinate = (abvecX * bcvecY) - (abvecY * bcvecX);

	ret = atan2(determinate, dotproduct);
;
	//converts the return value to degrees
	ret *= 180;
	ret = ret / pi;

	//if the angle is more than 180 it turns counter clockwise. 
	if (ret >= 180) {
		ret *= -1;
	}


	return ret;

}

Point grahamScan::NextToTop() {
	//used to get the point next to the top of the stack
	//mostly used to make the code look cleaner and make i
	//easier to read at func GrahamStack().
	Point top = this->m_Stack.top();//hold the top point so we can put it back onto the top of the stack
	Point nextTo; //holds the point under the top

	this->m_Stack.pop(); //pop point top from the stack 
	nextTo = this->m_Stack.top();// reads the point underneath the point that got poped

	this->m_Stack.push(top);//places the point that got poped back onto the stack

	return nextTo;//returns the point under the top point.
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

//calculates the bottomost point
void grahamScan::BottomMost(int x, int y) {
	//essentially just compares what would be the bottommost point
	//and if its further down it sets it at m_points[0]
	//which is the bottom most point 
	//then pushes the other point to the end of the list
	//it will be sorted later.
	Point point = Point(x, y);
	if (!this->m_Points.empty()) {
		if ((point.y) > (this->m_Points[0].y)) {
			this->m_Points.push_back(this->m_Points[0]);
			this->m_Points[0].x = point.x; 
			this->m_Points[0].y = point.y;
		}
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
					//pushes back the Point or reassigns to the front if it's the bottomost point
					this->BottomMost(event.mouseButton.x, event.mouseButton.y);
					
				}
			}
			
			if (event.type == sf::Event::KeyPressed) {
				//when enter is hit it calculates the Hull's stack
				if (event.key.code == sf::Keyboard::Enter) {
					if (this->m_Points.size() > 3) {
						this->GrahamStack();
					}
				}
			}

		}

		this->m_window->clear();

		//draws the dots everywhere the user clicked
		for (int i = 0; i < this->m_Points.size(); i++) {
			sf::CircleShape whitedot(3);
			whitedot.setPosition(this->m_Points[i].x - 2, this->m_Points[i].y -2 );
			this->m_window->draw(whitedot);
		}
		
		if (!this->m_Stack.empty()) {
			//gets a temp space to copy the main stack into it
			std::stack<Point> tempStack = this->m_Stack;

			//gets the first point from the stack so we know where the bottommost point is
			Point firstpoint = tempStack.top();
			//for the stack loop lower down.
			Point stackone = tempStack.top();
			tempStack.pop();

			//draws the first green dot.
			sf::CircleShape greendot(3);
			greendot.setFillColor(sf::Color::Green);
			greendot.setPosition((stackone.x - 2), (stackone.y - 2));
			this->m_window->draw(greendot);

			while (!tempStack.empty()) {
				//sets the second point to the next one in the stack
				Point stacktwo = tempStack.top();
				tempStack.pop();

				//draws the greendot at the second pos each loop
				greendot.setPosition((stackone.x - 2), (stackone.y - 2));
				this->m_window->draw(greendot);

				//draws the line between the two points
				this->DrawLine(stackone, stacktwo);

				//shuffles point two to point one. 
				stackone = stacktwo;

			}
			//drawing the green dot and a line to the first point to complete the hull.
			//draws the line from the last point to the first point
			this->DrawLine(firstpoint, stackone);
		}

		//setting the bottomost point to blue
		if (this->m_Points.size() > 0) {
			sf::CircleShape bluedot(3);
			bluedot.setPosition((this->m_Points[0].x - 2), (this->m_Points[0].y - 2));
			bluedot.setFillColor(sf::Color::Blue);
			this->m_window->draw(bluedot);
		}


		this->m_window->display();

	}


}
