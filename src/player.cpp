#include "player.h"
#include <iostream>
#include <string>

#define SCALE_HERO 0.36
#define MOVE_DISTANCE 0.5f
#define FLY_SPRITE_COUNT 2
#define SHOOT_SPRITE_COUNT 5

Player::Player(sf::Vector2f viewSize) : _viewSize(viewSize)
{
    playerTexture.loadFromFile("../Assets/Graphics/Plane/Fly_1.png");
    playerSprite.setTexture(playerTexture);
    playerTexture.setSmooth(true);
    playerSprite.scale(SCALE_HERO, SCALE_HERO);
    playerSprite.setPosition(sf::Vector2f(_viewSize.x / 2 , _viewSize.y / 2 ));
    playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);

    LoadSprites();

}

void Player::LoadSprites()
{
    sf::Texture tempTexture;
    sf::Sprite tempSprite;

    flySprite.resize(2);
    flyTexture.resize(2);

    shootSprite.resize(5);
    shootTexture.resize(5);

    std::cout << "Loading Sprites\n";

    for(int i = 0; i < FLY_SPRITE_COUNT; i++)
    {
        std::string assetString = "../Assets/Graphics/Plane/Fly_" + std::to_string(i+1) + ".png";
        flyTexture[i].loadFromFile(assetString);
        flySprite[i].setTexture(flyTexture[i]);
        flyTexture[i].setSmooth(true);
        flySprite[i].scale(SCALE_HERO, SCALE_HERO);
        flySprite[i].setPosition(sf::Vector2f(0 , _viewSize.y / 2 ));
        flySprite[i].setOrigin(0, flyTexture[i].getSize().y / 2);

        //flySprite.emplace_back(tempSprite);
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

    std::cout << "Loaded Sprites\n";

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

    if(++animateCount > 1000)
    {
        animateCount = 0;
        shooting = false;
    }

    if(shooting)
    {
        return shootSprite[shootCount];
    }


    return flySprite[flyCount];
}

void Player::Update(keys_t input, sf::Time frameRate)
{
    sf::Vector2f moveDistance(0,0);
    float dt = frameRate.asMilliseconds();

    switch (input)
    {
    case KEY_RIGHT:
        moveDistance.x = MOVE_DISTANCE * dt;
        break;
    case KEY_LEFT:
        moveDistance.x = -MOVE_DISTANCE * dt;
        break;
    case KEY_UP:
         moveDistance.y = -MOVE_DISTANCE * dt;
        break;
    case KEY_DOWN:
        moveDistance.y = MOVE_DISTANCE * dt;
        break;
    case KEY_SPACE:
        shooting = true;
        break;
    default:
        break;
    }

    for(int i = 0; i < FLY_SPRITE_COUNT; i++)
    {
        flySprite[i].move(moveDistance.x, moveDistance.y);
    }

    for(int i = 0; i < SHOOT_SPRITE_COUNT; i++)
    {
        shootSprite[i].move(moveDistance.x, moveDistance.y);
    }

    //flySprite[0].move(moveDistance.x, moveDistance.y);
}
