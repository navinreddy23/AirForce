#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

class Enemy
{
public:
    Enemy(sf::Vector2f viewSize);
    void Draw(sf::RenderWindow* window);
    void Update(sf::Time frameRate);
    sf::Sprite& GetSprite();
    bool Fire();
    void HasFired(void);
    sf::Vector2f GetPosition();

private:
    void LoadSprites();
    void LoadSounds();
    void ClockTrigger(void);

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
