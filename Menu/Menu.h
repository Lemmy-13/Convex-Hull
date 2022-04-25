#pragma once
#include <SFML/Graphics.hpp>
#define  MAX_ITEMS 4

class Menu
        {
public:
            Menu(float width, float height);
            ~Menu();

            void draw(sf::RenderWindow& window);
            void MoveUp();
            void MoveDown();
            int GetPressedItem() {return selectItem;}
private:
            int selectItem = 0;
            sf::Font font;
            sf::Text menu[MAX_ITEMS];
            sf::Text text;
};
