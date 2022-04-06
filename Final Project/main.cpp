#include <iostream>
#include <vector>
#include "ch.h"
#include <SFML/Graphics.hpp>

int main()
{
    //Creates the application window and adds the title.
    sf::RenderWindow window(sf::VideoMode(1400, 1050), "Convex Hull");

    //Vector
    std::vector<Point> points;

    //Check
    bool valid = false;

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
                    valid = true;
                }
            }
        }

        //Makes the background black.
        window.clear(sf::Color::Black);

        Polygon convex_hull = ConvexHull(points);
        sf::ConvexShape conv;
        conv.setFillColor(sf::Color::Black);
        conv.setOutlineThickness(3);
        conv.setOutlineColor(sf::Color::Green);
        conv.setPointCount(convex_hull.points.size());
        for (int i = 0; i < convex_hull.points.size(); ++i) {
            Point p = convex_hull.points[i];
            conv.setPoint(i, sf::Vector2f(p.x, p.y));
        }

        if (valid)
        {
            window.draw(conv);
        }

        for (const auto& r : points)
        {
            //Size of the circles.
            sf::CircleShape shape(8);

            //Circle position.
            shape.setPosition(r.x, r.y);

            //Circle color.
            shape.setFillColor(sf::Color::White);

            //Draw the shape.
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}
