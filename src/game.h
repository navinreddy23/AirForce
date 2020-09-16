#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"

#define FPS 60.0F

class Game
{
public:
    Game();
    void Run(void);

private:
    void HandleBullets(Player* Player, sf::Time TimerPerFrame);
    void HandleEnemy(sf::Time TimePerFrame, Player& Player);
    void Render(Player *Player);
    void HandleEnemyBulletCollision(void);
    void HandlePlayerEnemyCollision(Player& Player);
    void HandlePlayerBulletCollison(Player* Player);
    void SpawnEnemy(void);
    bool CheckCollision(sf::Sprite sprite1, sf::Sprite sprite2);

    void HandleExplosion();
    void AddExplosion(sf::FloatRect position);

    sf::RenderWindow window;
    sf::Texture skyTexture;
    sf::Sprite skySprite;
    sf::Vector2f viewSize;
    sf::VideoMode vm;

    std::vector <std::unique_ptr<Bullet>> bulletList;
    std::vector <std::unique_ptr<Enemy>> enemyList;
    std::vector <std::unique_ptr<Explosion>> explosionList;

    bool pause = false;

    Enemy* dummyEnemyPtr;
    Explosion* dummyExplosionPtr;
};

#endif // GAME_H
