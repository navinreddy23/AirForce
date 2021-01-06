#include "enemy.h"
#include <random>
#include <chrono>

#define SCALE_ENEMY 0.18
#define MOVE_DISTANCE_Y 0.1f
#define MOVE_DISTANCE_X 0.2f

#define VERT_MOV_START 0.65

Enemy::Enemy(sf::Vector2f viewSize) : _viewSize(viewSize)
{
    LoadSprites();
    LoadSounds();
}

Enemy::~Enemy()
{

}

void Enemy::LoadSprites(void)
{
    std::random_device rd;
    std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> distribution1(1, 4);
    std::uniform_int_distribution<> distribution2(100, _viewSize.y - 100);

    int i = distribution1(gen);
    float randomPosition = distribution2(gen);

    std::string assetString = "../Assets/Graphics/Enemy/plane_" + std::to_string(i) + ".png";
    _enemyTexture.loadFromFile(assetString);
    _enemySprite.setTexture(_enemyTexture);
    _enemyTexture.setSmooth(true);
    _enemySprite.scale(-SCALE_ENEMY, SCALE_ENEMY);
    _enemySprite.setPosition(sf::Vector2f(_viewSize.x, randomPosition));
    _enemySprite.setOrigin(0, _enemyTexture.getSize().y / 2);
}

void Enemy::LoadSounds()
{
    _bufferFire.loadFromFile("../Assets/Sounds/Cannon.wav");
    _soundFire.setBuffer(_bufferFire);
}

void Enemy::Draw(sf::RenderWindow* window)
{
    window->draw(_enemySprite);
}

void Enemy::Update(sf::Time frameRate, sf::Vector2f playerPosition, levels_t level)
{
    ClockTrigger(level);
    UpdateMovement(frameRate, playerPosition, level);
}

void Enemy::UpdateMovement(sf::Time frameRate, sf::Vector2f playerPosition, levels_t level)
{
    float dt = frameRate.asMilliseconds();
    sf::Vector2f moveDistance(0,0);

    float diffY = _enemySprite.getPosition().y - playerPosition.y;
    float diffX = _enemySprite.getPosition().x - playerPosition.x;

    if (diffY > 10 && (diffX < _viewSize.x * VERT_MOV_START))
    {
        moveDistance.y = -GetValue(ENEMY_SPEED_Y, level) * dt;
    }
    else if (diffY < -10 && (diffX < _viewSize.x * VERT_MOV_START))
    {
        moveDistance.y = GetValue(ENEMY_SPEED_Y, level) * dt;
    }

    moveDistance.x = -GetValue(ENEMY_SPEED_X, level) * dt;

    _enemySprite.move(moveDistance.x, moveDistance.y);
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
        _soundFire.play();
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

sf::Sprite& Enemy::GetSprite(void)
{
    return _enemySprite;
}

sf::Vector2f Enemy::GetPosition(void)
{
    sf::Vector2f adjustPosition;

    adjustPosition = _enemySprite.getPosition();
    adjustPosition.x -= 100;
    adjustPosition.y += 10;
    return adjustPosition;
}

void Enemy::ReduceLife(void)
{
    _lives -= 1;
}

int Enemy::GetLivesCount(void)
{
    return _lives;
}
