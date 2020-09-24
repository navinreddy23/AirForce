#include "player.h"
#include <string>
#include <SFML/Audio.hpp>

#define SCALE_HERO 0.36
#define MOVE_DISTANCE 0.009f
#define FLY_SPRITE_COUNT 2
#define SHOOT_SPRITE_COUNT 5

Player::Player(sf::Vector2f viewSize) : _viewSize(viewSize)
{
    LoadSprites();
    LoadSounds();
}

Player::~Player()
{

}

void Player::LoadSounds(void)
{
    _bufferFire.loadFromFile("../Assets/Sounds/Cannon.wav");
    _soundFire.setBuffer(_bufferFire);

    _bufferClink.loadFromFile("../Assets/Sounds/Coin.wav");
    _soundClink.setBuffer(_bufferClink);

    _bufferGameOver.loadFromFile("../Assets/Sounds/Gameover.wav");
    _soundGameOver.setBuffer(_bufferGameOver);
}

void Player::LoadSprites(void)
{
    _flySprite.resize(FLY_SPRITE_COUNT);
    _flyTexture.resize(FLY_SPRITE_COUNT);

    _shootSprite.resize(SHOOT_SPRITE_COUNT);
    _shootTexture.resize(SHOOT_SPRITE_COUNT);

    for (int i = 0; i < FLY_SPRITE_COUNT; i++)
    {
        std::string assetString = "../Assets/Graphics/Plane/Fly_" + std::to_string(i+1) + ".png";
        _flyTexture[i].loadFromFile(assetString);
        _flySprite[i].setTexture(_flyTexture[i]);
        _flyTexture[i].setSmooth(true);
        _flySprite[i].scale(SCALE_HERO, SCALE_HERO);
        _flySprite[i].setPosition(sf::Vector2f(0, _viewSize.y / 2 ));
        _flySprite[i].setOrigin(0, _flyTexture[i].getSize().y / 2);
    }

    for (int i = 0; i < SHOOT_SPRITE_COUNT; i++)
    {
        std::string assetString = "../Assets/Graphics/Plane/Shoot_" + std::to_string(i+1) + ".png";
        _shootTexture[i].loadFromFile(assetString);
        _shootSprite[i].setTexture(_shootTexture[i]);
        _shootTexture[i].setSmooth(true);
        _shootSprite[i].scale(SCALE_HERO, SCALE_HERO);
        _shootSprite[i].setPosition(sf::Vector2f(0 , _viewSize.y / 2 ));
        _shootSprite[i].setOrigin(0, _shootTexture[i].getSize().y / 2);
    }
}

void Player::Draw(sf::RenderWindow* window)
{
    window->draw(Animate());
}

sf::Sprite & Player::Animate(void)
{
    static int flyCount = 0, shootCount = 0, animateCount;

    if (++flyCount > (FLY_SPRITE_COUNT - 1))
    {
        flyCount = 0;
    }

    if (++shootCount > (SHOOT_SPRITE_COUNT - 1))
    {
        shootCount = 0;
    }

    if (++animateCount > 50)
    {
        animateCount = 0;
        _shootingAnimation = false;
    }

    if (_shootingAnimation)
    {
        _currentSprite = _shootSprite[shootCount];
        return _currentSprite;
    }

    if (_fireSound)
    {
        _fireSound = false;
        _soundFire.play();
    }

    _currentSprite = _flySprite[flyCount];
    return _currentSprite;
}

void Player::Update(keys_t input, sf::Time frameRate)
{
    switch (input)
    {
    case KEY_RIGHT_PRESS:
        _playerMovingRight = true;
        break;
    case KEY_LEFT_PRESS:
        _playerMovingLeft = true;
        break;
    case KEY_UP_PRESS:
         _playerMovingUp = true;
        break;
    case KEY_DOWN_PRESS:
        _playerMovingDown = true;
        break;
    case KEY_RIGHT_RELEASE:
        _playerMovingRight = false;
        break;
    case KEY_LEFT_RELEASE:
        _playerMovingLeft = false;
        break;
    case KEY_UP_RELEASE:
         _playerMovingUp = false;
        break;
    case KEY_DOWN_RELEASE:
        _playerMovingDown = false;
        break;
    case KEY_SPACE:
        _shootingAnimation = true;
        _fireSound = true;
        _spawnBullet = true;
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

    if (_playerMovingRight)
    {
        moveDistance.x = MOVE_DISTANCE * dt;
    }

    if (_playerMovingLeft)
    {
        moveDistance.x = -MOVE_DISTANCE * dt;
    }

    if (_playerMovingUp)
    {
        moveDistance.y = -MOVE_DISTANCE * dt;
    }

    if (_playerMovingDown)
    {
        moveDistance.y = MOVE_DISTANCE * dt;
    }


    for (int i = 0; i < FLY_SPRITE_COUNT; i++)
    {
        CheckAndSetBounds(_flySprite[i], moveDistance);
        _flySprite[i].move(moveDistance.x, moveDistance.y);
    }

    for (int i = 0; i < SHOOT_SPRITE_COUNT; i++)
    {
        CheckAndSetBounds(_shootSprite[i], moveDistance);
        _shootSprite[i].move(moveDistance.x, moveDistance.y);
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

    if (moveDistance.y + currentSprite.getPosition().y <= currentSprite.getGlobalBounds().height / 2)
    {
        moveDistance.y = 0;
    }
    else if (moveDistance.y + currentSprite.getPosition().y >= _viewSize.y - currentSprite.getGlobalBounds().height / 2)
    {
        moveDistance.y = 0;
    }
}

void Player::BulletFired(void)
{
    _spawnBullet = false;
}

bool Player::IsTriggerPressed(void)
{
    return _spawnBullet;
}

sf::Vector2f Player::GetPosition(void)
{
    sf::Vector2f adjustPosition;
    adjustPosition = _flySprite[0].getPosition();

    adjustPosition.x += 100;
    adjustPosition.y += 10;
    return adjustPosition;
}

sf::Sprite& Player::GetSprite(void)
{
    return _currentSprite;
}

void Player::PlayCoinSound(void)
{
    _soundClink.play();
}

void Player::PlayGameOverSound(void)
{
    _soundGameOver.play();
}

void Player::ResetLives(void)
{
    _lives = 3;
}

void Player::ResetState(void)
{
    _playerMovingUp = false;
    _playerMovingDown = false;
    _playerMovingLeft = false;
    _playerMovingRight = false;
}

void Player::ReduceLife(void)
{
    _lives -= 1;
}

void Player::IncreaseLife()
{
    _lives += 1;
}

int Player::GetLivesCount(void)
{
    return _lives;
}
