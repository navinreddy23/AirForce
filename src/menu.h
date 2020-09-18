#ifndef MENU_H
#define MENU_H

#include "game.h"
#include <SFML/Graphics.hpp>

class Menu : private Game
{
public:
    Menu();
    //Menu(sf::RenderWindow* window);
    ~Menu();
    void Run(sf::RenderWindow* windowPtr);

private:
    void LoadSprites();
    void Render(sf::RenderWindow* windowPtr);


    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    sf::Texture menuTexture;
    sf::Sprite  menuSprite;
};

#endif // MENU_H
