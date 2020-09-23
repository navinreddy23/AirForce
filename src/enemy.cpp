#include "enemy.h"
#include <iostream>
#include <random>
#include <chrono>

#define SCALE_ENEMY 0.18
#define MOVE_DISTANCE_Y 0.1f
#define MOVE_DISTANCE_X 0.2f

#define VERT_MOV_START 0.75

Enemy::Enemy(sf::Vector2f viewSize) : _viewSize(viewSize)
{
    LoadSprites();
    LoadSounds();
}

Enemy::~Enemy()
{
    std::cout << "Enemy: Destructor called" << std::endl;
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
    //std::cout << "Enemy: Loaded Sprites" << std::endl;
}

void Enemy::LoadSounds()
{
    //std::cout << "Enemy: Loaded Sounds" << std::endl;
    bufferFire.loadFromFile("../Assets/Sounds/Cannon.wav");
    soundFire.setBuffer(bufferFire);
}

void Enemy::Draw(sf::RenderWindow* window)
{
    window->draw(enemySprite);
}

void Enemy::Update(sf::Time frameRate, sf::Vector2f playerPosition, levels_t level)
{
    ClockTrigger(level);
    UpdateMovement(frameRate, playerPosition, level);

    //std::cout << "Enemy x: " << GetValue(ENEMY_SPEED_X, level) << std::endl;

}

void Enemy::UpdateMovement(sf::Time frameRate, sf::Vector2f playerPosition, levels_t level)
{
    float dt = frameRate.asMilliseconds();
    sf::Vector2f moveDistance(0,0);

    //std::cout << "*********   dt: " << dt << std::endl;

    //std::cout << "Enemy y: " << enemySprite.getPosition().y << " Player y: " << playerPosition.y << std::endl;

    float diffY = enemySprite.getPosition().y - playerPosition.y;
    float diffX = enemySprite.getPosition().x - playerPosition.x;

    //std::cout << "Diff: " << diff << std::endl;

    if (diffY > 10 && (diffX < _viewSize.x * VERT_MOV_START))
    {
        moveDistance.y = -GetValue(ENEMY_SPEED_Y, level) * dt;
        //std::cout << "************************Move down************" << std::endl;
    }
    else if (diffY < -10 && (diffX < _viewSize.x * VERT_MOV_START))
    {
        moveDistance.y = GetValue(ENEMY_SPEED_Y, level) * dt;
        //std::cout << "************************Move up************" << std::endl;
    }

    moveDistance.x = -GetValue(ENEMY_SPEED_X, level) * dt;

    enemySprite.move(moveDistance.x, moveDistance.y);
}

void Enemy::ClockTrigger(levels_t level)
{
    static size_t millis;
    int min = 0, max = 0;

    if (!_clockStarted)
    {
        _startTime = std::chrono::system_clock::now();
        _clockStarted = true;

        min = GetValue(BULLET_SPWAWN_MIN, level);
        max = GetValue(BULLET_SPAWN_MAX, level);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribution(min, max);
        millis = distribution(gen);
    }

    _endTime = std::chrono::system_clock::now();

    size_t diff = std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count();

    if (diff >= millis)
    {
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

void Enemy::ReduceLife()
{
    _lives -= 1;
}

int Enemy::GetLivesCount()
{
    return _lives;
}
