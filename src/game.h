#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "coin.h"
#include "level_manager.h"

typedef struct
{
    bool showInitMenu = true;
    int highScore;
    bool pause = false;
    bool newGame = false;
    bool gameOver = false;
} game_menu_interface_t;

typedef game_menu_interface_t interface_t;


class Game : LevelManager
{
public:
    Game();
    void Run(void);

private:
    void Init(sf::RenderWindow* window);
    void LoadFonts();
    void ResetGame(Player& Player);
    void HandleBullets(Player* Player, sf::Time TimerPerFrame);
    void HandleEnemy(sf::Time TimePerFrame, Player& Player);
    void HandleCoins(Player* Player);
    void Render(Player *Player, sf::RenderWindow* window);
    void HandleEnemyBulletCollision(void);
    void HandlePlayerEnemyCollision(Player& Player);
    void HandlePlayerBulletCollison(Player* Player);
    void HandlePlayerCoinCollision(Player* Player);
    void SpawnEnemy(void);
    void SpawnCoins(void);
    bool CheckCollision(sf::Sprite sprite1, sf::Sprite sprite2);
    void CheckEnemyLives();
    bool IsGameOver(Player& Player);

    void HandleExplosion();
    void AddExplosion(sf::FloatRect position);
    void UpdateHighScore();
    void SetScoreAndLives(Player &Player);

    void UpdateLevel();

    int _score = 0;
    int _highScore = 0;
    interface_t* _gameState;

    sf::Texture _skyTexture;
    sf::Sprite _skySprite;
    sf::Vector2f _viewSize;
    sf::VideoMode _vm;

    sf::Font _gameFont;
    sf::Text _scoreText;
    std::string _scoreString;

    std::vector <std::unique_ptr<Bullet>> _bulletList;
    std::vector <std::unique_ptr<Enemy>> _enemyList;
    std::vector <std::unique_ptr<Explosion>> _explosionList;
    std::vector <std::unique_ptr<Coin>> _coinList;

    levels_t _currentLevel = LEVEL_1;
};

#endif // GAME_H
