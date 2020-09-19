#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"

typedef struct
{
    bool showInitMenu = true;
    int highScore;
    bool pause = false;
    bool newGame = false;
} game_menu_interface_t;

typedef game_menu_interface_t interface_t;


class Game
{
public:
    Game();
    void Run(void);
    int GetScore();
    void SetScore(int value);

protected:

    bool GetPauseState();
    bool GetMenuState();

private:
    void Init(sf::RenderWindow* window);
    void ResetGame();
    void HandleBullets(Player* Player, sf::Time TimerPerFrame);
    void HandleEnemy(sf::Time TimePerFrame, Player& Player);
    void Render(Player *Player, sf::RenderWindow* window);
    void HandleEnemyBulletCollision(void);
    void HandlePlayerEnemyCollision(Player& Player);
    void HandlePlayerBulletCollison(Player* Player);
    void SpawnEnemy(void);
    bool CheckCollision(sf::Sprite sprite1, sf::Sprite sprite2);

    void HandleExplosion();
    void AddExplosion(sf::FloatRect position);

    bool pause = false;
    bool showInitMenu;
    int score = 23;


    sf::Texture skyTexture;
    sf::Sprite skySprite;
    sf::Vector2f viewSize;
    sf::VideoMode vm;

    std::vector <std::unique_ptr<Bullet>> bulletList;
    std::vector <std::unique_ptr<Enemy>> enemyList;
    std::vector <std::unique_ptr<Explosion>> explosionList;

    //sf::RenderWindow window;
};

#endif // GAME_H
