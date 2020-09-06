#include "bullet.h"
#include <iostream>

#define BULLET_SPRITE_COUNT 5
#define BULLET_SIZE         0.25
#define ANIMATE_SPEED       500
#define MOVE_DISTANCE       0.5
Bullet::Bullet()
{
    LoadSprites();
}

Bullet::~Bullet()
{
    std::cout << "Bullet destructor called" << std::endl;
}

void Bullet::LoadSprites()
{
    bulletTexture.resize(BULLET_SPRITE_COUNT);
    bulletSprite.resize(BULLET_SPRITE_COUNT);

    std::cout << "Loading Sprites" << std::endl;

    for(int i = 0; i < BULLET_SPRITE_COUNT; i++)
    {
        std::string assetString = "../Assets/Graphics/Bullet/Bullet_" + std::to_string(i+1) + ".png";
        bulletTexture[i].loadFromFile(assetString);
        bulletSprite[i].setTexture(bulletTexture[i]);
        bulletTexture[i].setSmooth(true);
        bulletSprite[i].scale(BULLET_SIZE, BULLET_SIZE);
    }

    std::cout << "Loaded Sprites" << std::endl;

}

void Bullet::Draw(sf::RenderWindow* window)
{
    window->draw(Animate());
}

sf::Sprite & Bullet::Animate()
{
    static int bulletCount = 0, animateCount;

    if(++animateCount > ANIMATE_SPEED)
    {
        animateCount = 0;
        bulletCount++;
    }

    if(bulletCount > (BULLET_SPRITE_COUNT - 1))
    {
        bulletCount = 0;
    }

    return bulletSprite[bulletCount];
}

void Bullet::Update(sf::Time frameRate)
{
    sf::Vector2f moveDistance;
    float dt = frameRate.asMilliseconds();

    moveDistance.x = MOVE_DISTANCE * dt;

    for (int i = 0; i < BULLET_SPRITE_COUNT; i++)
    {
        bulletSprite[i].move(moveDistance.x, 0);
    }
}

void Bullet::SetPosition(sf::Vector2f playerPosition)
{
    for (int i = 0; i < BULLET_SPRITE_COUNT; i++)
    {
         bulletSprite[i].setPosition(playerPosition);
    }
}

sf::Vector2f Bullet::GetPosition()
{
    return bulletSprite[0].getPosition();
}

void Bullet::SetOwner(bulletOwner_t owner)
{
    _owner = owner;
}

bulletOwner_t Bullet::GetOwner(void)
{
    return _owner;
}
