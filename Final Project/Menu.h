#pragma once
#include "VisualConvexHull.h"
#include "Finger.h"
#define  MAX_ITEMS 4

class Menu
        {
public:
            Menu(float width, float height);
            ~Menu();

            void runMenu(float width, float height);
            void runVisHull();
            void runReadHull();
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
