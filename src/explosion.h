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
    void LoadSprites(void);
    sf::Sprite& Animate(void);
    void LoadSounds(void);

    std::vector <sf::Texture> _explosionTexture;
    std::vector <sf::Sprite> _explosionSprite;

    sf::SoundBuffer _bufferFire;
    sf::Sound _soundFire;

    sf::Vector2f _position;

    bool _explode = true;
    bool _playSound = true;
};

#endif // EXPLOSION_H
