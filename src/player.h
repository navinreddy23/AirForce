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
    ~Player();
    void Draw(sf::RenderWindow* window);
    void Update(keys_t input, sf::Time dt);
    void BulletFired();
    bool IsTriggerPressed();
    sf::Vector2f GetPosition();

private:
    void LoadSprites(void);
    void LoadSounds(void);
    sf::Sprite& Animate(void);
    void CheckAndSetBounds(sf::Sprite &currentSprite, sf::Vector2f &moveDistance);
    void UpdateMovement(sf::Time frameRate);

    std::vector <sf::Texture> flyTexture;
    std::vector <sf::Sprite> flySprite;
    std::vector <sf::Texture> shootTexture;
    std::vector <sf::Sprite> shootSprite;

    sf::SoundBuffer bufferFire;
    sf::Sound soundFire;

    sf::Vector2f _viewSize;

    bool shootingAnimation = false;
    bool fireSound = false;
    bool spawnBullet = false;

    bool playerMovingRight = false;
    bool playerMovingLeft = false;
    bool playerMovingUp = false;
    bool playerMovingDown = false;
};

#endif // PLAYER_H
