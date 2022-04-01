#include <iostream>
#include <vector>
#include "ch.h"
#include <SFML/Graphics.hpp>

//Count how many clicks
int number_of_points;

int main()
{
    //Creates the application window and adds the title.
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Convex Hull");
    //Vector to save points shapes.
    std::vector<sf::CircleShape> points;

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

                //Circle's outline size.
                shape.setOutlineThickness(3);

                //Add
                points.push_back(shape);

                //Counts the clicks
                ++number_of_points;
            }

            //Adds Keyboard
            else if (event.type == sf::Event::KeyPressed)
            {
                //Space bar to stop and compute.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    std::cout << number_of_points << "\n";
                    window.close();
                }
            }
        }
        window.clear();
        for (const auto& r : points)
            window.draw(r);
        window.display();
    }
}
