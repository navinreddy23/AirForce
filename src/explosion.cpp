#include "explosion.h"

#define SPRITE_COUNT 9
#define SPRITE_SIZE  0.4

#define ANIMATE_SPEED 150

Explosion::Explosion(sf::Vector2f position) : _position(position)
{
    LoadSprites();
    LoadSounds();
}

void Explosion::LoadSounds(void)
{
    _bufferFire.loadFromFile("../Assets/Sounds/Explosion.wav");
    _soundFire.setBuffer(_bufferFire);
}

Explosion::~Explosion()
{

}

void Explosion::LoadSprites(void)
{
    _explosionTexture.resize(SPRITE_COUNT);
    _explosionSprite.resize(SPRITE_COUNT);

     for(int i = 0; i < SPRITE_COUNT; i++)
     {
         std::string assetString = "../Assets/Graphics/Explosion/Explosion_" + std::to_string(i+1) + ".png";
         _explosionTexture[i].loadFromFile(assetString);
         _explosionSprite[i].setTexture(_explosionTexture[i]);
         _explosionTexture[i].setSmooth(true);
         _explosionSprite[i].setPosition(_position);
         _explosionSprite[i].scale(SPRITE_SIZE, SPRITE_SIZE);
     }
}

void Explosion::Draw(sf::RenderWindow* window)
{
    if (_explode)
        window->draw(Animate());
}

sf::Sprite& Explosion::Animate(void)
{
    static int explosionIndex = 0, animateCount;

    if(_playSound)
    {
        _soundFire.play();
        _playSound = false;
    }

    if(++animateCount > ANIMATE_SPEED)
    {
        animateCount = 0;
        explosionIndex++;
    }

    if(explosionIndex > (SPRITE_COUNT - 1))
    {
        explosionIndex = 0;
        _explode = false;
    }

    return _explosionSprite[explosionIndex];
}

bool Explosion::IsExplodeComplete()
{
    return !_explode;
}
