#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if(!font.loadFromFile("MenuFiles/FSEX300.ttf"))
    {

    }

    //Logo
    text.setFont(font);
    text.setCharacterSize(150);
    text.setFillColor(sf::Color::Yellow);
    text.setString("Convex Hull");
    text.setPosition(550.f, 50.f);

    //Option 1
    menu[0].setFont(font);
    menu[0].setCharacterSize(65);
    menu[0].setFillColor(sf::Color::Green);
    menu[0].setString("Click or Touch");
    menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2));

    //Option 2
    menu[1].setFont(font);
    menu[1].setCharacterSize(65);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Read from a File \n");
    menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 2) * 3));

    //Option 3
    menu[2].setFont(font);
    menu[2].setCharacterSize(65);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Finger Count\n");
    menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 3) * 4));

    //Option 4
    menu[3].setFont(font);
    menu[3].setCharacterSize(65);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Exit");
    menu[3].setOrigin(menu[3].getLocalBounds().width / 2, menu[3].getLocalBounds().height / 2);
    menu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 4) * 5));

    runMenu(width, height);
}

Menu::~Menu()
{

}

//Loop to display on the screen

//used to run the visual Convex hull from the menu
void Menu::runVisHull() {
    //his name is jerry 
    visualConvexHull jerry = visualConvexHull(); //a visual hull object to be run in the menu
    jerry.visualConvexHullRun();
}

//used to run the menu that will promt the user into different parts of the program as menus do.
void Menu::runMenu(float width, float height) {
    sf::RenderWindow window(sf::VideoMode(width, height), "Menu");

    // -- Background -- //
    float frame_time = (float)1 / (float)60;
    sf::Texture background;
    if (!background.loadFromFile("MenuFiles/BG1.jpg"))
        exit(1);
    background.setRepeated(true);

    sf::Sprite stars(background);

    int posx = 0;

    sf::Clock clock;
    sf::Time passed_time;
    // ---------- //

    //Menu size
    //Menu menu(window.getSize().x, window.getSize().y);

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
                    this->MoveUp();
                    break;

                case sf::Keyboard::Down:
                    this->MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (this->GetPressedItem())
                    {
                    case 0:
                        std::cout << "Option 1 was pressed" << std::endl;
                        //Here
                        window.close();//closes the menu window
                        this->runVisHull();//runs the visualConvexHull run thing
                        runMenu(width, height);//after the visual convexhull window closes/finishes the menu will run again.
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
            this->draw(window);
            window.display();

            passed_time -= sf::seconds(frame_time);

        }

    }
}

void Menu::draw(sf::RenderWindow& window)
{
    //Logo
    window.draw(text);

    //Menu loop
    for(int i = 0; i < MAX_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

//Up movement
void  Menu::MoveUp()
{
    if (selectItem - 1 >= 0)
    {
        menu[selectItem].setFillColor(sf::Color::White);
        selectItem--;
        menu[selectItem].setFillColor(sf::Color::Green);
    }
}

//Down movement
void  Menu::MoveDown()
{
    if (selectItem + 1 < MAX_ITEMS)
    {
        menu[selectItem].setFillColor(sf::Color::White);
        selectItem++;
        menu[selectItem].setFillColor(sf::Color::Green);
    }
}