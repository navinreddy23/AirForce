#include "coin.h"
#include <iostream>
#include <random>

#define COIN_SIZE           0.5
#define COIN_SPRITE_COUNT   30

#define ANIMATE_SPEED       100

Coin::Coin(sf::Vector2f viewSize) : _viewSize(viewSize)
{
    LoadSprites();
}

Coin::~Coin()
{

}

void Coin::LoadSprites()
{
    coinTexture.resize(COIN_SPRITE_COUNT);
    coinSprite.resize(COIN_SPRITE_COUNT);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution1(_viewSize.x * 0.2, _viewSize.x * 0.6);
    std::uniform_int_distribution<> distribution2(_viewSize.y * 0.1, _viewSize.y * 0.9);
    std::uniform_int_distribution<> distribution3(SILVER_COIN, GOLD_COIN);

    int coin = distribution3(gen);

    std::cout << "Coin: Loading Sprites" << std::endl;

    std::string assetString;



    for(int i = 0; i < COIN_SPRITE_COUNT; i++)
    {
        if (coin == SILVER_COIN)
        {
            assetString = "../Assets/Graphics/Coins/Silver_" + std::to_string(i+1) + ".png";
            _coinType = SILVER_COIN;
        }
        else if (coin == GOLD_COIN)
        {
            assetString = "../Assets/Graphics/Coins/Gold_" + std::to_string(i+1) + ".png";
            _coinType = GOLD_COIN;
        }

        coinTexture[i].loadFromFile(assetString);
        coinSprite[i].setTexture(coinTexture[i]);
        coinTexture[i].setSmooth(true);
        coinSprite[i].scale(COIN_SIZE, COIN_SIZE);
    }



    sf::Vector2f position;
    position.x = distribution1(gen);
    position.y = distribution2(gen);

    SetPosition(position);


    std::cout << "Coin: Loaded Sprites" << std::endl;
}

void Coin::SetPosition(sf::Vector2f position)
{
    std::cout << "Coin position: " << position.x << ", " << position.y << std::endl;
    for (int i = 0; i < COIN_SPRITE_COUNT; i++)
    {
         coinSprite[i].setPosition(position);
    }
}

void Coin::Draw(sf::RenderWindow* window)
{
    window->draw(Animate());
}

sf::Sprite& Coin::Animate()
{
    static int coinIndex = 0, animateCount;

    if(++animateCount > ANIMATE_SPEED)
    {
        animateCount = 0;
        coinIndex++;
    }

    if(coinIndex > (COIN_SPRITE_COUNT - 1))
    {
        coinIndex = 0;
    }

    currentSprite = coinSprite[coinIndex];
    return currentSprite;
}

sf::Sprite& Coin::GetSprite()
{
    return currentSprite;
}

coin_type_t Coin::GetCoinType()
{
    return _coinType;
}
