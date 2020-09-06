#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"
#include "bullet.h"

#define FPS 60.0F

class Game
{
public:
    Game();
    void Run(void);

private:
    void HandlePlayerBullet(Player* Player);
     void Render(Player *Player);

    sf::RenderWindow window;
    sf::Texture skyTexture;
    sf::Sprite skySprite;
    sf::Vector2f viewSize;
    sf::VideoMode vm;

    std::vector <std::unique_ptr<Bullet>> bulletVec;
};

#endif // GAME_H
