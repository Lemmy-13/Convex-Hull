#include "Menu.h"

Menu::Menu(float width, float height)
{
    if(!font.loadFromFile("/Users/lemmy/Documents/Projects/Menu/FSEX300.ttf"))
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

}

Menu::~Menu()
{

}

//Loop to display on the screen
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