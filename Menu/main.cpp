#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "iostream"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Menu");

    // -- Background -- //
    float frame_time = (float) 1 / (float) 60;
    sf::Texture background;
    if (!background.loadFromFile("/Users/lemmy/Documents/Projects/Menu/BG1.jpg"))
        exit(1);
    background.setRepeated(true);

    sf::Sprite stars(background);

    int posx = 0;

    sf::Clock clock;
    sf::Time passed_time;
    // ---------- //

    //Menu size
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) 
            {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up:
                            menu.MoveUp();
                            break;

                        case sf::Keyboard::Down:
                            menu.MoveDown();
                            break;

                        case sf::Keyboard::Return:
                            switch (menu.GetPressedItem())
                            {
                                case 0:
                                    std::cout << "Option 1 was pressed" << std::endl;
                                    //Here
                                    break;
                                case 1:
                                    std::cout << "Option 2 was pressed" << std::endl;
                                    //Here
                                    break;
                                case 2:
                                    std::cout << "Option 3 was pressed" << std::endl;
                                    //Here
                                    break;
                                case 3:
                                    std::cout << "Option 4 was pressed(exit)" << std::endl;
                                    window.close();
                                    break;
                            }
                    }
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        passed_time += clock.restart();
        while (passed_time.asSeconds() >= frame_time) {

            stars.setTextureRect(sf::IntRect(posx, 0, window.getSize().x, window.getSize().y));
            posx += 2;

            window.clear();
            window.draw(stars);
            menu.draw(window);
            window.display();

            passed_time -= sf::seconds(frame_time);

        }

    }

    return 0;
}