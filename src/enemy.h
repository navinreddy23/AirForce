#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Enemy
{
public:
    Enemy(sf::Vector2f viewSize);
    void Draw(sf::RenderWindow* window);
    sf::Sprite& GetSprite();

private:
    void LoadSprites();
    void LoadSounds();

    sf::Texture enemyTexture;
    sf::Sprite  enemySprite;

    sf::SoundBuffer bufferFire;
    sf::Sound soundFire;

    sf::Vector2f _viewSize;
};

#endif // ENEMY_H
