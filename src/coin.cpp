#include "coin.h"
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

void Coin::LoadSprites(void)
{
    _coinTexture.resize(COIN_SPRITE_COUNT);
    _coinSprite.resize(COIN_SPRITE_COUNT);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution1(_viewSize.x * 0.2, _viewSize.x * 0.6);
    std::uniform_int_distribution<> distribution2(_viewSize.y * 0.1, _viewSize.y * 0.9);
    std::uniform_int_distribution<> distribution3(SILVER_COIN, GOLD_COIN);

    int coin = distribution3(gen);

    std::string assetString;

    for (int i = 0; i < COIN_SPRITE_COUNT; i++)
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

        _coinTexture[i].loadFromFile(assetString);
        _coinSprite[i].setTexture(_coinTexture[i]);
        _coinTexture[i].setSmooth(true);
        _coinSprite[i].scale(COIN_SIZE, COIN_SIZE);
    }

    sf::Vector2f position;

    position.x = distribution1(gen);
    position.y = distribution2(gen);

    SetPosition(position);
}

void Coin::SetPosition(sf::Vector2f position)
{
    for (int i = 0; i < COIN_SPRITE_COUNT; i++)
    {
         _coinSprite[i].setPosition(position);
    }
}

void Coin::Draw(sf::RenderWindow* window)
{
    window->draw(Animate());
}

sf::Sprite& Coin::Animate(void)
{
    static int coinIndex = 0, animateCount;

    if (++animateCount > ANIMATE_SPEED)
    {
        animateCount = 0;
        coinIndex++;
    }

    if (coinIndex > (COIN_SPRITE_COUNT - 1))
    {
        coinIndex = 0;
    }

    _currentSprite = _coinSprite[coinIndex];
    return _currentSprite;
}

sf::Sprite& Coin::GetSprite(void)
{
    return _currentSprite;
}

coin_type_t Coin::GetCoinType(void)
{
    return _coinType;
}
