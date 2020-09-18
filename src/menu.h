#ifndef MENU_H
#define MENU_H

#include "game.h"
#include <SFML/Graphics.hpp>

class Menu : private Game
{
public:
    //Menu();
    Menu(sf::RenderWindow* window, sf::Vector2f viewSize);
    ~Menu();
    void Run();

private:
    void LoadSprites();
    void LoadFonts();
    void Render();

    sf::RenderWindow* _window;

    sf::Vector2f _viewSize;


    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    sf::Texture menuTexture;
    sf::Sprite  menuSprite;

    sf::Font gameFont;
    sf::Text gameNameText;
};

#endif // MENU_H
