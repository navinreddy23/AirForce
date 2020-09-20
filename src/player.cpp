#include "player.h"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

#define SCALE_HERO 0.36
#define MOVE_DISTANCE 0.006f
#define FLY_SPRITE_COUNT 2
#define SHOOT_SPRITE_COUNT 5

Player::Player(sf::Vector2f viewSize) : _viewSize(viewSize)
{
    LoadSprites();
    LoadSounds();
}

Player::~Player()
{
     std::cout << "Player destructor called" << std::endl;
}

void Player::LoadSounds()
{
    std::cout << "Loaded Sounds" << std::endl;
    bufferFire.loadFromFile("../Assets/Sounds/Cannon.wav");
    soundFire.setBuffer(bufferFire);

    bufferClink.loadFromFile("../Assets/Sounds/Coin.wav");
    soundClink.setBuffer(bufferClink);

}

void Player::LoadSprites()
{
    flySprite.resize(FLY_SPRITE_COUNT);
    flyTexture.resize(FLY_SPRITE_COUNT);

    shootSprite.resize(SHOOT_SPRITE_COUNT);
    shootTexture.resize(SHOOT_SPRITE_COUNT);

    std::cout << "Loading Sprites" << std::endl;

    for(int i = 0; i < FLY_SPRITE_COUNT; i++)
    {
        std::string assetString = "../Assets/Graphics/Plane/Fly_" + std::to_string(i+1) + ".png";
        flyTexture[i].loadFromFile(assetString);
        flySprite[i].setTexture(flyTexture[i]);
        flyTexture[i].setSmooth(true);
        flySprite[i].scale(SCALE_HERO, SCALE_HERO);
        flySprite[i].setPosition(sf::Vector2f(0, _viewSize.y / 2 ));
        flySprite[i].setOrigin(0, flyTexture[i].getSize().y / 2);
    }

    for (int i = 0; i < SHOOT_SPRITE_COUNT; i++)
    {
        std::string assetString = "../Assets/Graphics/Plane/Shoot_" + std::to_string(i+1) + ".png";
        shootTexture[i].loadFromFile(assetString);
        shootSprite[i].setTexture(shootTexture[i]);
        shootTexture[i].setSmooth(true);
        shootSprite[i].scale(SCALE_HERO, SCALE_HERO);
        shootSprite[i].setPosition(sf::Vector2f(0 , _viewSize.y / 2 ));
        shootSprite[i].setOrigin(0, shootTexture[i].getSize().y / 2);
    }

    std::cout << "Loaded Sprites" << std::endl;

}

void Player::Draw(sf::RenderWindow* window)
{
    window->draw(Animate());
}

sf::Sprite & Player::Animate()
{
    static int flyCount = 0, shootCount = 0, animateCount;

    if(++flyCount > (FLY_SPRITE_COUNT - 1))
    {
        flyCount = 0;
    }

    if(++shootCount > (SHOOT_SPRITE_COUNT - 1))
    {
        shootCount = 0;
    }

    if(++animateCount > 50)
    {
        animateCount = 0;
        shootingAnimation = false;
    }

    if(shootingAnimation)
    {
        currentSprite = shootSprite[shootCount];
        return currentSprite;
    }

    if(fireSound)
    {
        fireSound = false;
        soundFire.play();
    }

    currentSprite = flySprite[flyCount];
    return currentSprite;
}

void Player::Update(keys_t input, sf::Time frameRate)
{
    switch (input)
    {
    case KEY_RIGHT_PRESS:
        playerMovingRight = true;
        break;
    case KEY_LEFT_PRESS:
        playerMovingLeft = true;
        break;
    case KEY_UP_PRESS:
         playerMovingUp = true;
        break;
    case KEY_DOWN_PRESS:
        playerMovingDown = true;
        break;
    case KEY_RIGHT_RELEASE:
        playerMovingRight = false;
        break;
    case KEY_LEFT_RELEASE:
        playerMovingLeft = false;
        break;
    case KEY_UP_RELEASE:
         playerMovingUp = false;
        break;
    case KEY_DOWN_RELEASE:
        playerMovingDown = false;
        break;
    case KEY_SPACE:
        shootingAnimation = true;
        fireSound = true;
        spawnBullet = true;
        break;
    default:
        break;
    }

    UpdateMovement(frameRate);
}

void Player::UpdateMovement(sf::Time frameRate)
{
    sf::Vector2f moveDistance(0,0);
    float dt = frameRate.asMilliseconds();

    if(playerMovingRight)
    {
        moveDistance.x = MOVE_DISTANCE * dt;
    }

    if(playerMovingLeft)
    {
        moveDistance.x = -MOVE_DISTANCE * dt;
    }

    if(playerMovingUp)
    {
        moveDistance.y = -MOVE_DISTANCE * dt;
    }

    if(playerMovingDown)
    {
        moveDistance.y = MOVE_DISTANCE * dt;
    }


    for (int i = 0; i < FLY_SPRITE_COUNT; i++)
    {
        CheckAndSetBounds(flySprite[i], moveDistance);
        flySprite[i].move(moveDistance.x, moveDistance.y);
    }

    for(int i = 0; i < SHOOT_SPRITE_COUNT; i++)
    {
        CheckAndSetBounds(shootSprite[i], moveDistance);
        shootSprite[i].move(moveDistance.x, moveDistance.y);
    }

}

void Player::CheckAndSetBounds(sf::Sprite& currentSprite, sf::Vector2f& moveDistance)
{
    if (moveDistance.x + currentSprite.getPosition().x >= _viewSize.x - currentSprite.getGlobalBounds().width)
    {
        moveDistance.x = 0;
    }
    else if (currentSprite.getPosition().x + moveDistance.x <= 0)
    {
        moveDistance.x = 0;
    }

    if(moveDistance.y + currentSprite.getPosition().y <= currentSprite.getGlobalBounds().height / 2)
    {
        moveDistance.y = 0;
    }
    else if (moveDistance.y + currentSprite.getPosition().y >= _viewSize.y - currentSprite.getGlobalBounds().height / 2)
    {
        moveDistance.y = 0;
    }
}

void Player::BulletFired()
{
    spawnBullet = false;
}

bool Player::IsTriggerPressed()
{
    return spawnBullet;
}

sf::Vector2f Player::GetPosition()
{
    sf::Vector2f adjustPosition;
    adjustPosition = flySprite[0].getPosition();

    adjustPosition.x += 100;
    adjustPosition.y += 10;
    return adjustPosition;
}

sf::Sprite& Player::GetSprite()
{
    return currentSprite;
}

void Player::PlayCoinSound()
{
    std::cout << "Sound Played" << std::endl;
    soundClink.play();
}
