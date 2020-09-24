#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>
#include <vector>

typedef enum
{
    SILVER_COIN,
    GOLD_COIN
}coin_type_t;

class Coin
{
public:
    Coin(sf::Vector2f viewSize);
    ~Coin();
    void Draw(sf::RenderWindow* window);
    sf::Sprite& GetSprite(void);
    coin_type_t GetCoinType(void);

private:
    void LoadSprites(void);
    sf::Sprite& Animate(void);
    void SetPosition(sf::Vector2f position);

    std::vector <sf::Texture> _coinTexture;
    std::vector <sf::Sprite> _coinSprite;

    sf::Vector2f _viewSize;
    sf::Sprite _currentSprite;

    coin_type_t _coinType;
};

#endif // COIN_H
