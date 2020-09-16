#include "enemy.h"
#include <iostream>
#include <random>
#include <chrono>

#define SCALE_ENEMY 0.18

Enemy::Enemy(sf::Vector2f viewSize) : _viewSize(viewSize)
{
    LoadSprites();
    LoadSounds();
}


void Enemy::LoadSprites()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution1(1, 4);
    std::uniform_int_distribution<> distribution2(100, _viewSize.y - 100);

    int i = distribution1(gen);
    float randomPosition = distribution2(gen);

    std::string assetString = "../Assets/Graphics/Enemy/plane_" + std::to_string(i) + ".png";
    enemyTexture.loadFromFile(assetString);
    enemySprite.setTexture(enemyTexture);
    enemyTexture.setSmooth(true);
    enemySprite.scale(-SCALE_ENEMY, SCALE_ENEMY);
    enemySprite.setPosition(sf::Vector2f(_viewSize.x, randomPosition));
    enemySprite.setOrigin(0, enemyTexture.getSize().y / 2);
    std::cout << "Enemy: Loaded Sprites" << std::endl;
}

void Enemy::LoadSounds()
{
    std::cout << "Enemy: Loaded Sounds" << std::endl;
    bufferFire.loadFromFile("../Assets/Sounds/Cannon.wav");
    soundFire.setBuffer(bufferFire);
}

void Enemy::Draw(sf::RenderWindow* window)
{
    window->draw(enemySprite);
}

void Enemy::Update(sf::Time frameRate)
{
    ClockTrigger();
}

void Enemy::ClockTrigger(void)
{
    size_t millis = 1000;

    if (!_clockStarted)
    {
        _startTime = std::chrono::system_clock::now();
        _clockStarted = true;
    }

    _endTime = std::chrono::system_clock::now();

    size_t diff = std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count();

    if (diff >= millis)
    {
        std::cout << "Timer expired" << std::endl;
        soundFire.play();
        _fire = true;
        _clockStarted = false;
    }
}

bool Enemy::Fire(void)
{
    return _fire;
}

void Enemy::HasFired(void)
{
    _fire = false;
}

sf::Sprite& Enemy::GetSprite()
{
    return enemySprite;
}

sf::Vector2f Enemy::GetPosition()
{
    sf::Vector2f adjustPosition;
    adjustPosition = enemySprite.getPosition();

    adjustPosition.x -= 100;
    adjustPosition.y += 10;
    return adjustPosition;
}
