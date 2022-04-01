#include <iostream>
#include <vector>
#include "ch.h"
#include <SFML/Graphics.hpp>

//Counts how many clicks
int number_of_points;

int main()
{
    //Creates the application window and adds the title.
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Convex Hull");

    //Vector
    std::vector<Point> points;

    //Check
    int valid;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

                //Adds Mouse.
            else if (event.type == sf::Event::MouseButtonPressed &&
                     event.mouseButton.button == sf::Mouse::Left)
            {
                //Gets the x & y coordinates.
                float x = event.mouseButton.x;
                float y = event.mouseButton.y;

                //Save here.
                Point p(x, y);
                if (find(points.begin(), points.end(), p) == points.end())
                    points.push_back(p);
            }

                //Adds Keyboard
            else if (event.type == sf::Event::KeyPressed)
            {
                //Space bar to stop and compute.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {

                    // Find the bottommost point
                    int xmin = points[0].x, min = 0;
                    for (int i = 1; i < points.size(); i++)
                    {
                        int x = points[i].x;

                        // Pick the bottom-most or chose the left
                        // most point in case of tie
                        if ((x < xmin) || (xmin == x &&
                                           points[i].y < points[min].y))
                        {
                            xmin = points[i].x, min = i;
                        }
                    }

                    //Passing the value to valid.
                    valid = xmin;

                    //Print Bottommost Point.
                    std::cout << "Bottommost Point: " << xmin << "\n";
                }
            }
        }

        //Makes the background black.
        window.clear(sf::Color::Black);

        for (const auto& r : points)
        {
            //Size of the circles.
            sf::CircleShape shape(6);

            //Circle position.
            shape.setPosition(r.x, r.y);

            //Checks the points to decide the bottom-most or chose the left.
            if (r.x == valid)
            {
                //Circle color.
                shape.setFillColor(sf::Color::Green);
            }
            else
            {
                //Circle color.
                shape.setFillColor(sf::Color::White);
            }

            //Draw the shape.
            window.draw(shape);
        }
        window.display();
    }
}
