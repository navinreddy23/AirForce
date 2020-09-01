#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "controller.h"
#include <vector>

class Player
{
public:
    Player(sf::Vector2f viewSize);
    void Draw(sf::RenderWindow* window);
    void Update(keys_t input, sf::Time dt);
    void LoadSprites(void);
    sf::Sprite & Animate();
private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    std::vector <sf::Texture> flyTexture;
    std::vector <sf::Sprite> flySprite;
    std::vector <sf::Texture> shootTexture;
    std::vector <sf::Sprite> shootSprite;
    sf::Vector2f _viewSize;
    bool shooting = false;
};

#endif // PLAYER_H
