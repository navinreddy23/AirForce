#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

class Enemy
{
public:
    Enemy(sf::Vector2f viewSize);
    ~Enemy(void);
    void Draw(sf::RenderWindow* window);
    void Update(sf::Time frameRate, sf::Vector2f playerPosition);
    sf::Sprite& GetSprite();
    bool Fire();
    void HasFired(void);
    sf::Vector2f GetPosition();

    void ReduceLife();
    int GetLivesCount();

private:
    void LoadSprites();
    void LoadSounds();
    void ClockTrigger(void);
    void UpdateMovement(sf::Time, sf::Vector2f playerPosition);

    int _lives = 3;

    sf::Texture enemyTexture;
    sf::Sprite  enemySprite;

    sf::SoundBuffer bufferFire;
    sf::Sound soundFire;

    sf::Vector2f _viewSize;

    bool _fire = false;
    bool _clockStarted = false;
    std::chrono::time_point<std::chrono::system_clock> _startTime;
    std::chrono::time_point<std::chrono::system_clock> _endTime;
};

#endif // ENEMY_H
