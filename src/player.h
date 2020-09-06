#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "controller.h"
#include <vector>

class Player
{
public:
    Player(sf::Vector2f viewSize);
    void Draw(sf::RenderWindow* window);
    void Update(keys_t input, sf::Time dt);
    void LoadSprites(void);
    void LoadSounds(void);
    sf::Sprite & Animate(void);
private:
    void CheckAndSetBounds(sf::Sprite &currentSprite, sf::Vector2f &moveDistance);
    std::vector <sf::Texture> flyTexture;
    std::vector <sf::Sprite> flySprite;
    std::vector <sf::Texture> shootTexture;
    std::vector <sf::Sprite> shootSprite;
    sf::Vector2f _viewSize;
    bool shooting = false;
    bool fireSound = false;

    sf::SoundBuffer bufferFire;
    sf::Sound soundFire;
};

#endif // PLAYER_H
