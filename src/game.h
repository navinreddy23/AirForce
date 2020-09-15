#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"
#include "bullet.h"
#include "enemy.h"

#define FPS 60.0F

class Game
{
public:
    Game();
    void Run(void);

private:
    void HandlePlayerBullet(Player* Player, sf::Time TimerPerFrame);
    void HandleEnemy(void);
    void Render(Player *Player);
    void HandleEnemyBulletCollision(void);
    bool CheckCollision(sf::Sprite sprite1, sf::Sprite sprite2);

    sf::RenderWindow window;
    sf::Texture skyTexture;
    sf::Sprite skySprite;
    sf::Vector2f viewSize;
    sf::VideoMode vm;

    std::vector <std::unique_ptr<Bullet>> bulletList;
    std::vector <std::unique_ptr<Enemy>> enemyList;

    Enemy* dummyEnemyPtr;
};

#endif // GAME_H
