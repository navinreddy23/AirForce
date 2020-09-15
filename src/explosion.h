#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
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

    std::vector <sf::Texture> explosionTexture;
    std::vector <sf::Sprite> explosionSprite;

    sf::Vector2f _position;

    bool explode = true;
};

#endif // EXPLOSION_H
