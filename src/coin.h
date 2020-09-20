#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    sf::Sprite& GetSprite();
    coin_type_t GetCoinType(void);
    void PlaySound(void);
private:
    void LoadSprites();
    sf::Sprite &Animate();
    void SetPosition(sf::Vector2f position);

    std::vector <sf::Texture> coinTexture;
    std::vector <sf::Sprite> coinSprite;

    sf::Vector2f _viewSize;
    sf::Sprite currentSprite;

    coin_type_t _coinType;
};

#endif // COIN_H
