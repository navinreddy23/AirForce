#include "bullet.h"

#define BULLET_SPRITE_COUNT 5
#define BULLET_SIZE         0.25
#define ANIMATE_SPEED       50
#define MOVE_DISTANCE       1

Bullet::Bullet()
{
    LoadSprites();
}

Bullet::~Bullet()
{

}

void Bullet::LoadSprites()
{
    _bulletTexture.resize(BULLET_SPRITE_COUNT);
    _bulletSprite.resize(BULLET_SPRITE_COUNT);

    for (int i = 0; i < BULLET_SPRITE_COUNT; i++)
    {
        std::string assetString = "../Assets/Graphics/Bullet/Bullet_" + std::to_string(i+1) + ".png";
        _bulletTexture[i].loadFromFile(assetString);
        _bulletSprite[i].setTexture(_bulletTexture[i]);
        _bulletTexture[i].setSmooth(true);
        _bulletSprite[i].scale(BULLET_SIZE, BULLET_SIZE);
    }

    _currentSprite = _bulletSprite[0];
}

void Bullet::Draw(sf::RenderWindow* window)
{
    if (!stopDrawing)
        window->draw(Animate());
}

sf::Sprite& Bullet::Animate()
{
    static int bulletIndex = 0, animateCount;

    if (++animateCount > ANIMATE_SPEED)
    {
        animateCount = 0;
        bulletIndex++;
    }

    if (bulletIndex > (BULLET_SPRITE_COUNT - 1))
    {
        bulletIndex = 0;
    }

    _currentSprite = _bulletSprite[bulletIndex];
    return _currentSprite;
}

void Bullet::Update(sf::Time frameRate, levels_t level)
{
    sf::Vector2f moveDistance;
    float dt = frameRate.asMilliseconds();

    if (_owner == PLAYERS_BULLET)
    {
        moveDistance.x = MOVE_DISTANCE * dt;
    }
    else if (_owner == ENEMYS_BULLET)
    {
        moveDistance.x = -GetValue(BULLET_SPEED, level) * dt;
    }

    for (int i = 0; i < BULLET_SPRITE_COUNT; i++)
    {
        _bulletSprite[i].move(moveDistance.x, 0);
    }
}

void Bullet::SetPosition(sf::Vector2f playerPosition)
{
    for (int i = 0; i < BULLET_SPRITE_COUNT; i++)
    {
         _bulletSprite[i].setPosition(playerPosition);
    }
}

sf::Vector2f Bullet::GetPosition()
{
    return _bulletSprite[0].getPosition();
}

void Bullet::SetOwner(bulletOwner_t owner)
{
    _owner = owner;
}

bulletOwner_t Bullet::GetOwner(void)
{
    return _owner;
}

sf::Sprite& Bullet::GetSprite()
{
    return _currentSprite;
}

void Bullet::Invalidate(void)
{
    stopDrawing = true;
    _owner = UNASSIGNED;
}
