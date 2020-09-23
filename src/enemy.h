#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include "level_manager.h"

class Enemy : LevelManager
{
public:
    Enemy(sf::Vector2f viewSize);
    ~Enemy(void);

    void Draw(sf::RenderWindow* window);
    void Update(sf::Time frameRate, sf::Vector2f playerPosition, levels_t level);
    sf::Sprite& GetSprite(void);
    bool Fire(void);
    void HasFired(void);
    sf::Vector2f GetPosition(void);
    void ReduceLife(void);
    int GetLivesCount(void);

private:
    void LoadSprites(void);
    void LoadSounds(void);
    void ClockTrigger(levels_t level);
    void UpdateMovement(sf::Time, sf::Vector2f playerPosition, levels_t level);

    int _lives = 3;

    sf::Texture _enemyTexture;
    sf::Sprite  _enemySprite;

    sf::SoundBuffer _bufferFire;
    sf::Sound _soundFire;

    sf::Vector2f _viewSize;

    bool _fire = false;
    bool _clockStarted = false;
    std::chrono::time_point<std::chrono::system_clock> _startTime;
    std::chrono::time_point<std::chrono::system_clock> _endTime;
};

#endif // ENEMY_H
