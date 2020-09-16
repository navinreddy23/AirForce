#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Explosion
{
public:
    Explosion(sf::Vector2f position);
    ~Explosion();
    void Draw(sf::RenderWindow* window);
    bool IsExplodeComplete(void);
private:
    void LoadSprites();
    sf::Sprite& Animate();
    void LoadSounds();

    std::vector <sf::Texture> explosionTexture;
    std::vector <sf::Sprite> explosionSprite;

    sf::SoundBuffer bufferFire;
    sf::Sound soundFire;

    sf::Vector2f _position;

    bool explode = true;
    bool playSound = true;
};

#endif // EXPLOSION_H
