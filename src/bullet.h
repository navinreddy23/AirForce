#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "level_manager.h"

typedef enum
{
    UNASSIGNED,
    PLAYERS_BULLET,
    ENEMYS_BULLET
}bulletOwner_t;

class Bullet : LevelManager
{
public:
    Bullet();
    ~Bullet();
    void Draw(sf::RenderWindow* window);
    void Update(sf::Time frameRate, levels_t level);
    void SetPosition(sf::Vector2f playerPosition);
    sf::Vector2f GetPosition();
    sf::Sprite& GetSprite();
    void SetOwner(bulletOwner_t owner);
    bulletOwner_t GetOwner(void);

private:
    void LoadSprites();
    sf::Sprite &Animate();

    std::vector <sf::Texture> _bulletTexture;
    std::vector <sf::Sprite> _bulletSprite;

    sf::Sprite _currentSprite;
    sf::Vector2f _viewSize;
    bulletOwner_t _owner = UNASSIGNED;
};

#endif // BULLET_H
