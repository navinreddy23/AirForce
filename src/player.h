#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "controller.h"
#include <vector>

#define DEFAULT_PLAYER_SPEED 0.065f

class Player
{
public:
    Player(sf::Vector2f viewSize);
    ~Player();

    void Draw(sf::RenderWindow* window);
    void Update(keys_t input, sf::Time dt);
    void BulletFired(void);
    bool IsTriggerPressed(void);
    sf::Vector2f GetPosition(void);
    sf::Sprite& GetSprite(void);
    void PlayCoinSound(void);
    void PlayGameOverSound(void);
    void DisplayDead();

    void ResetLives(void);
    void ResetState(void);
    void ReduceLife(void);
    void IncreaseLife(void);
    void IncreaseSpeed(void);
    int GetLivesCount(void);

private:
    void LoadSprites(void);
    void LoadSounds(void);
    sf::Sprite& Animate(void);
    void CheckAndSetBounds(sf::Sprite &_currentSprite, sf::Vector2f &moveDistance);
    void UpdateMovement(sf::Time frameRate);

    float _moveDistance = DEFAULT_PLAYER_SPEED;

    std::vector <sf::Texture> _flyTexture;
    std::vector <sf::Sprite> _flySprite;
    std::vector <sf::Texture> _shootTexture;
    std::vector <sf::Sprite> _shootSprite;

    sf::Texture _playerDeadTexture;
    sf::Sprite _playerDeadSprite;

    sf::SoundBuffer _bufferFire;
    sf::Sound _soundFire;

    sf::SoundBuffer _bufferClink;
    sf::Sound _soundClink;

    sf::SoundBuffer _bufferGameOver;
    sf::Sound _soundGameOver;

    sf::Vector2f _viewSize;
    sf::Sprite _currentSprite;

    int _lives = 3;

    bool _shootingAnimation = false;
    bool _fireSound = false;
    bool _spawnBullet = false;

    bool _playerMovingRight = false;
    bool _playerMovingLeft = false;
    bool _playerMovingUp = false;
    bool _playerMovingDown = false;
};

#endif // PLAYER_H
