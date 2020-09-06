#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <vector>

typedef enum
{
    Unassigned,
    PlayersBullet,
    EnemiesBullet
}bulletOwner_t;

class Bullet
{
public:
    Bullet();
    ~Bullet();
    void Draw(sf::RenderWindow* window);
    void Update(sf::Time frameRate);
    void SetPosition(sf::Vector2f playerPosition);
    sf::Vector2f GetPosition();
    void SetOwner(bulletOwner_t owner);
    bulletOwner_t GetOwner(void);
private:
    void LoadSprites();
    sf::Sprite &Animate();

    std::vector <sf::Texture> bulletTexture;
    std::vector <sf::Sprite> bulletSprite;
    sf::Vector2f _viewSize;
    bulletOwner_t _owner = Unassigned;
};

#endif // BULLET_H
