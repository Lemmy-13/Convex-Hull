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

    std::vector<Point> points;

    //Vector to save points shapes.
    std::vector<sf::CircleShape> circle;

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

                //Size of the circle.
                sf::CircleShape shape(6);

                //Click position.
                shape.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

                //Circle color.
                shape.setFillColor(sf::Color::White);

                //Add
                circle.push_back(shape);

                //Counts the clicks
                ++number_of_points;

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
                    int ymin = points[0].y, min = 0;
                    for (int i = 1; i < number_of_points; i++)
                    {
                        int y = points[i].y;

                        // Pick the bottom-most or chose the left
                        // most point in case of tie
                        if ((y < ymin) || (ymin == y &&
                                           points[i].x < points[min].x))
                            ymin = points[i].y, min = i;
                    }

                    std::cout << "Bottommost Point " << ymin << "\n";
                }
            }
        }

        //Makes the background black.
        window.clear(sf::Color::Black);

        for (const auto& r : circle)
            window.draw(r);
        window.display();
    }
}
