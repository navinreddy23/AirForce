#include "explosion.h"
#include <iostream>

#define SPRITE_COUNT 9
#define SPRITE_SIZE  0.4

#define ANIMATE_SPEED 150

Explosion::Explosion(sf::Vector2f position) : _position(position)
{
    LoadSprites();
}

Explosion::~Explosion()
{
    std::cout << "Explosion: Destructor called" << std::endl;
}

void Explosion::LoadSprites()
{
    explosionTexture.resize(SPRITE_COUNT);
    explosionSprite.resize(SPRITE_COUNT);

     std::cout << "Explosion: Loading Sprites" << std::endl;

     for(int i = 0; i < SPRITE_COUNT; i++)
     {
         std::string assetString = "../Assets/Graphics/Explosion/Explosion_" + std::to_string(i+1) + ".png";
         explosionTexture[i].loadFromFile(assetString);
         explosionSprite[i].setTexture(explosionTexture[i]);
         explosionTexture[i].setSmooth(true);
         explosionSprite[i].setPosition(_position);
         explosionSprite[i].scale(SPRITE_SIZE, SPRITE_SIZE);
     }

     std::cout << "Explosion: Loaded Sprites" << std::endl;
}


void Explosion::Draw(sf::RenderWindow* window)
{
    if (explode)
        window->draw(Animate());
}

sf::Sprite& Explosion::Animate()
{
    static int explosionCount = 0, animateCount;

    if(++animateCount > ANIMATE_SPEED)
    {
        animateCount = 0;
        explosionCount++;
    }

    if(explosionCount > (SPRITE_COUNT - 1))
    {
        explosionCount = 0;
        explode = false;
    }


    return explosionSprite[explosionCount];
}

bool Explosion::IsExplodeComplete()
{
    return !explode;
}
