#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


typedef long long ll;
struct Point {
    ll x, y;
    Point(ll a, ll b) :x(a), y(b) {};
    Point() {};
    bool operator<(const Point &rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

std::vector<Point> point;

ll ccw(Point pt1, Point pt2, Point pt3) {
    ll ret = pt1.x*pt2.y + pt2.x*pt3.y + pt3.x*pt1.y;
    ret -= (pt2.x*pt1.y + pt3.x*pt2.y + pt1.x*pt3.y);
    return ret;
}
ll dist(Point pt1, Point pt2) {
    ll dx = pt2.x - pt1.x;
    ll dy = pt2.y - pt1.y;
    return dx * dx + dy * dy;
}


int main()
{
    //Creates the application window and adds the title.
    sf::RenderWindow window(sf::VideoMode(1400, 1050), "Convex Hull");

    //Check
    //bool valid = false;

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

                Point p(x, y);

                    point.push_back(p);

                std::vector<Point> hull;
                std::swap(point[0], *min_element(point.begin(), point.end()));
                sort(point.begin() + 1, point.end(), [](Point x, Point y) {
                    ll cw = ccw(point[0], x, y);
                    if (cw == 0) return dist(point[0], x) < dist(point[0], y);
                    return cw > 0;
                });


            }

                //Adds Keyboard
            else if (event.type == sf::Event::KeyPressed)
            {
                //Space bar to stop and compute.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    //valid = true;
                }
            }
        }

        //Makes the background black.
        window.clear(sf::Color::Black);


        sf::ConvexShape conv;
        conv.setFillColor(sf::Color::Black);
        conv.setOutlineThickness(3);
        conv.setOutlineColor(sf::Color::Green);
        conv.setPointCount(point.size());
        for (int i = 0; i < point.size(); ++i) {
            Point p = point[i];
            conv.setPoint(i, sf::Vector2f(p.x, p.y));
        }

        //if (valid)
        //{
            window.draw(conv);
        //}

        for (const auto& r : point)
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
