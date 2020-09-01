#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.h"

#define FPS 60.0F

class Game
{
public:
    Game();
    void Run(void);
    void Render(Player *Player);


private:
    sf::RenderWindow window;
    sf::Texture skyTexture;
    sf::Sprite skySprite;
    sf::Vector2f viewSize;
    sf::VideoMode vm;
};

#endif // GAME_H
