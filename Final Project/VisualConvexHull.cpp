#include "VisualConvexHull.h"
#include <iostream>
#include <sstream>

//constructors
visualConvexHull::visualConvexHull() {
	//this->h_graham = grahamScan();
	this->waitSeconds = 1000;
}

visualConvexHull::visualConvexHull(std::vector<Point> points) {
	//this->h_graham = grahamScan(points);
	this->waitSeconds = 1000;
}

//private functions

Point visualConvexHull::NextToTop() {
	//same as the one from grahamScan just modified for visualConvexHull

	//used to get the point next to the top of the stack
	//mostly used to make the code look cleaner and make i
	//easier to read at func GrahamStack().
	Point top = this->h_visualStack.top();//hold the top point so we can put it back onto the top of the stack
	Point nextTo; //holds the point under the top

	this->h_visualStack.pop(); //pop point top from the stack 
	nextTo = this->h_visualStack.top();// reads the point underneath the point that got poped

	this->h_visualStack.push(top);//places the point that got poped back onto the stack

	return nextTo;//returns the point under the top point.
}

bool visualConvexHull::VisualStack(int count) {
	//should only be run if there are more than 3 points
	this->h_graham.SortPoints();
	/*int pointSize = this->h_graham.m_Points.size();*/

	//cylces through the points in the list.
	count = count % (this->h_graham.m_Points.size());
	if (this->h_graham.m_Points.size() > 2) {
		//draws point being checked blue.
		sf::CircleShape bluedot(6);
		bluedot.setPosition((this->h_graham.m_Points[count].x - 2), (this->h_graham.m_Points[count].y - 2));
		bluedot.setFillColor(sf::Color::Yellow);
		this->h_graham.m_window->draw(bluedot);

		
		if (this->h_visualStack.size() > 1 &&
			this->h_graham.ClockwiseTurn(this->h_visualStack.top(), this->NextToTop(), this->h_graham.m_Points[count]) >= 0)
			//while the top of the stack has to turn clockwise to look at the next point
			//pop the point from the stack and compare the next top of the stack
		{
			//draw redLine to signal fail.
			this->DrawRedLine(this->h_visualStack.top(), this->h_graham.m_Points[count]);
			//write failed dot to vector
			this->h_redDots.push_back(this->h_visualStack.top());
			//pop the stack
			this->h_visualStack.pop();
			return false;
		}
		//push the point into the stack
		this->h_visualStack.push(this->h_graham.m_Points[count]);
		//draw greenline to signal success
		if (this->h_visualStack.size() > 1) {
			this->DrawGreenLine(this->NextToTop(), this->h_graham.m_Points[count]);
		}
		return true;

	}
}

void visualConvexHull::DrawRedLine(Point p1, Point p2) {

	//used to draw a blue line between two points
	sf::VertexArray line(sf::Lines, 2);

	//setting pos
	line[0].position = sf::Vector2f(p1.x, p1.y);
	line[1].position = sf::Vector2f(p2.x, p2.y);

	//setting color
	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;

	//drawing it to the grahmScan object window. 
	this->h_graham.m_window->draw(line);
}

void visualConvexHull::DrawGreenLine(Point p1, Point p2) {

	//used to draw a blue line between two points
	sf::VertexArray line(sf::Lines, 2);

	//setting pos
	line[0].position = sf::Vector2f(p1.x, p1.y);
	line[1].position = sf::Vector2f(p2.x, p2.y);

	//setting color
	line[0].color = sf::Color::Green;
	line[1].color = sf::Color::Green;

	//drawing it to the grahmScan object window. 
	this->h_graham.m_window->draw(line);
}

std::vector<Point> visualConvexHull::readfile(std::string file_name) {
	// Create the input filestream - opens the file & prepares it for reading
	std::ifstream file(file_name);

	// Creates a temporary vector to represent one row
	std::vector<int> raw_coords;
	std::pair<int, int> coords;
	// Temporary string to hold a single line of the file
	std::string str;

	//a return vector of points
	std::vector<Point> pointVec;

	// Reads all lines in the file, 1 at at time
	while (std::getline(file, str)) {
		// Converts our string into a stringstream
		std::istringstream ss(str);
		// Temp double to store a converted value from a line
		int token;
		
		//A temp Point to iterate into a list
		//Point tempoint = Point();

		// Reads all values from the stringstream (current row), converts to double
		while (ss >> token) {
			// Adds the converted value to the row
			raw_coords.push_back(token);
			//std::cout << token;
		}
		pointVec.push_back(Point(raw_coords[0],raw_coords[1]));
		/*tempoint.x = raw_coords[0];
		tempoint.y = raw_coords[1];*/
		// Pushes our constructed vector of doubles to the 2D vector
		//pointVec.push_back(tempoint);
		raw_coords.clear();
	}
	return pointVec;
}

void visualConvexHull::runReadFile() {
	std::vector<Point> readfilevec = this->readfile("/Users/lemmy/Documents/Projects/Finalito/testfile1.txt");
	for (int x = 0; x < readfilevec.size(); x++) {
		this->h_graham.BottomMost(readfilevec[x].x, readfilevec[x].y);
	}
	this->visualConvexHullRun();
}


//public functions

void visualConvexHull::visualConvexHullRun() {
	//sets the title of the window to the correct title. 
	this->h_graham.m_window->setTitle("Convex Hull");
	//declaring variables 
	bool enter_pressed = false;	//used to determine if enter was pressed and will
	//go through an entire convexHull visual before returning to false.
	bool action = false;	//used to determine if something was drawn in order to 
	//incorporate a delay at the end of the loop
	int count = 0;		//used to count what point in the grahamscan.m_points is being compared

	bool hold = true; //used to indicate if the final convex hull will be kept on the screen
	bool lastrun = false; //used to determine if the first point was added to the top of the stack
	//also determines if graham scan is finished drawing. neaded for holding the hull on screen
	//if the hold bool is set to true. 

	bool pause = false;	//used to determine if the program should be paused.


	while (this->h_graham.m_window->isOpen()) {
		//Process events
		sf::Event event;

		while (this->h_graham.m_window->pollEvent(event))
		{
			//Close window if they click exit.
			if (event.type == sf::Event::Closed) {
				this->h_graham.m_window->close();
			}

			//button presses

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//pushes back the Point or reassigns to the front if it's the bottomost point
					if ((!enter_pressed ||
						(enter_pressed && lastrun))
						&& !pause) {
						this->h_graham.BottomMost(event.mouseButton.x, event.mouseButton.y);
                        std::cout << "Numbers: " << this->h_graham.m_Points.size() << std::endl;
					}
				}
			}

			if (event.type == sf::Event::KeyPressed) {
				//when enter is hit it calculates the Hull's stack
				if (event.key.code == sf::Keyboard::Enter) {
					//only if there are at least 3 points
					if (this->h_graham.m_Points.size() > 2) {
						if (hold && lastrun) {
							this->h_redDots.clear();
							this->h_visualStack = std::stack<Point>();
							count = 0;
							lastrun = false;
						}

						enter_pressed = true;
					}
				}
				//m decreases the delay between each draw to a min of .5 seconds
				if (event.key.code == sf::Keyboard::M) {
					if (this->waitSeconds > 500) {
						this->waitSeconds -= 500;
						std::cout << this->waitSeconds << std::endl;
					}
				}
				//n increases the delay to a max of 10 seconds 
				if (event.key.code == sf::Keyboard::N) {
					if (this->waitSeconds < 10000) {
						this->waitSeconds += 500;
						std::cout << this->waitSeconds << std::endl;
					}
				}
				//p sets the hold to true so the code will hold the final convex hull at the end
				if (event.key.code == sf::Keyboard::P) {
					hold = true;
					std::cout << "Hold is on" << std::endl;
				}
				//o will set it to false so it doens't hold it 
				if (event.key.code == sf::Keyboard::O) {
					hold = false;
					std::cout << "Hold is off" << std::endl;
				}
				//will cause the convex hull to instantly draw like the orgininal GrahamScan-convexhull
				if (event.key.code == sf::Keyboard::T) {
					if (this->waitSeconds == 0) {
						this->waitSeconds = 500;
						std::cout << "Speed set to 500" << std::endl;
					}
					else if (this->waitSeconds > 0) {
						this->waitSeconds = 0;
						std::cout << "Speed set to instant" << std::endl;
					}
				}
				//Will pause in middraw 
				if (event.key.code == sf::Keyboard::Space) {
					if (pause) {
						pause = false;
						std::cout << "Not Paused" << std::endl;
					}
					else if (!pause) {
						pause = true;
						std::cout << "Paused" << std::endl;
					}
				}

			}

		}

		if (!pause) {

			this->h_graham.m_window->clear();

			//draws the dots where the user clicked
			for (int i = 0; i < this->h_graham.m_Points.size(); i++) {
				sf::CircleShape whitedot(6);
				whitedot.setPosition(this->h_graham.m_Points[i].x - 2, this->h_graham.m_Points[i].y - 2);
				this->h_graham.m_window->draw(whitedot);

                int game = h_graham.m_Points.size();

                sf::Text text1;
                sf::Font font1;

                if(!font1.loadFromFile("/Users/lemmy/Documents/Projects/Finalito/Menufiles/FSEX300.ttf"))
                {

                }

                text1.setFont(font1);
                text1.setCharacterSize(150);
                text1.setFillColor(sf::Color::Yellow);
                std::stringstream ss;  // #include <sstream>
                ss << game;
                text1.setString( ss.str().c_str() );
                text1.setPosition(70.f, 600.f);

                this->h_graham.m_window->draw(text1);
			}

			//this draws the blues lines and green dots between each item
			//that is in the stack at the time. 
			//is responsible for turning the dots green and making the confirmed lines
			//blue
			if (enter_pressed &&
				this->h_visualStack.size() > 1) {
				std::stack<Point> tempStack = this->h_visualStack;
				while (tempStack.size() > 1) {
					Point temp = tempStack.top();

					sf::CircleShape greendot(6);
					greendot.setFillColor(sf::Color::Green);
					greendot.setPosition((temp.x - 2), (temp.y - 2));
					this->h_graham.m_window->draw(greendot);

					tempStack.pop();
					this->h_graham.DrawLine(temp, tempStack.top());
				}
			}

			//this should be the very first iteration and this is used to
			//skip the delay of the first stack iteration because it's just
			//point 0 being added to the stack so nothing gets drawn but
			//there would still be an initial delay.
			if (enter_pressed &&
				count == 0 &&
				this->h_graham.m_Points.size() > 2) {

				this->VisualStack(count);
				count++;

			}

			//this is where most of the calculations are done through visualstack.
			else if (
				enter_pressed &&
				count < this->h_graham.m_Points.size() && !lastrun) {

				//if visualstack returns true that means the point it the top
				//of the stack turned counterclockwise to look at the point
				//grahamscan.m_points[count], and the algorithim can look at the next
				//point
				if (this->VisualStack(count)) {
					count++;
				}
				//action is set to true so that the delay will be cast at the end.
				action = true;
			}

			//this draws all the red dots that failed counterclockwise test, and won't
			//be included in the final stack iteration.
			if (enter_pressed &&
				!this->h_redDots.empty()) {
				for (int i = 0; i < this->h_redDots.size(); i++) {
					sf::CircleShape reddot(6);
					reddot.setPosition((this->h_redDots[i].x - 2), (this->h_redDots[i].y - 2));
					reddot.setFillColor(sf::Color::Red);
					this->h_graham.m_window->draw(reddot);
				}
			}


			//drawing the bottomost point to blue if enter hasn't been pressed
			//if enter has been pressed the point being compared should be blue.
			if (this->h_graham.m_Points.size() > 0 &&
				(!enter_pressed || lastrun)) {
				sf::CircleShape bluedot(6);
				bluedot.setPosition((this->h_graham.m_Points[0].x - 2), (this->h_graham.m_Points[0].y - 2));
				bluedot.setFillColor(sf::Color::Yellow);
				this->h_graham.m_window->draw(bluedot);
			}

			//should be the final iteration bascially just clears eveything
			//so that the user can enter more points and then hit enter
			//and have it iterate again. 
			if (count == (this->h_graham.m_Points.size()) &&
				enter_pressed &&
				!action) {
				//will run one more time to add the first point to the top of the stack.
				//mostly just used for the continous run. 
				if (!lastrun) {
					this->VisualStack(count);
					lastrun = true; //also used to determine if grahamscan has finished running.
				}

				//if hold isn't activated then it clear the data sets like usual
				if (!hold) {
					action = true;
					enter_pressed = false;
					this->h_redDots.clear();
					this->h_visualStack = std::stack<Point>();
					count = 0;
					lastrun = false;
				}
			}


			this->h_graham.m_window->display();

			//this is what makes the delay so the user can see everything be 
			//drawn one at a time. 
			if (action)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(this->waitSeconds));
				action = false;
			}

		}
	}

}