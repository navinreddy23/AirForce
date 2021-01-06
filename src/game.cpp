#include "game.h"
#include "menu.h"
#include <random>

#define RESOLUTION_X 1280
#define RESOLUTION_Y 720

#define SCALE_BACKGROUND 1

#define FPS 60.0f

Game::Game()
{

}

void Game::Init(sf::RenderWindow* window)
{
    _viewSize.x = RESOLUTION_X;
    _viewSize.y = RESOLUTION_Y;

    _vm.width = _viewSize.x;
    _vm.height = _viewSize.y;

    window->create(_vm, "AirForce");
    window->setFramerateLimit(FPS);


    _skyTexture.loadFromFile("../Assets/Graphics/Background_1.png");

    _skySprite.setTexture(_skyTexture);
    _skyTexture.setSmooth(true);
    _skySprite.scale(1, 0.75);

    LoadFonts();
}

void Game::LoadFonts()
{
    _gameFont.loadFromFile("../Assets/Fonts/Font.ttf");

    _scoreText.setFont(_gameFont);
    _scoreText.setString("Score");
    _scoreText.setCharacterSize(45);
    _scoreText.setFillColor(sf::Color::White);

    _scoreText.setPosition(sf::Vector2f(_viewSize.x * 0.05, _viewSize.y * 0.02));

    sf::FloatRect localBounds = _scoreText.getLocalBounds();
    _scoreText.setOrigin(localBounds.width / 2, localBounds.height / 2);
}

void Game::Run(void)
{
    sf::RenderWindow window;
    Init(&window);

    interface_t gameState;
    _gameState = &gameState;

    //Game objects
    Menu Menu(&window, _viewSize);
    Controller Controller;
    Player Player(_viewSize);

    //Initial menu
    gameState.showInitMenu = true;
    Menu.Run(&gameState);
    gameState.showInitMenu = false;

    //Clock initialization
    const sf::Time TimePerFrame =  sf::seconds(1.0f / FPS);

    while (window.isOpen())
    {
        keys_t key = Controller.HandleInput(&window);

        if (key == KEY_ESCAPE_PRESS)
            gameState.pause = true;

        if (gameState.newGame)
        {
            ResetGame(Player);
            //Reset complete
            gameState.newGame = false;
        }

        if (!gameState.pause)
            Player.Update(key, TimePerFrame);

        // Update Game
        Player.Update(Controller.HandleInput(&window), TimePerFrame);
        HandleBullets(Player, TimePerFrame);
        HandleEnemy(TimePerFrame, Player);
        HandleExplosion();
        HandleCoins(Player);
        UpdateLevel();

        //Render
        if (!gameState.pause) Render(Player, &window);

        UpdateHighScore();

        SetScoreAndLives(Player);

        if (IsGameOver(Player) || gameState.pause)
        {
            if (IsGameOver(Player))
            {
                Player.PlayGameOverSound();
                Player.DisplayDead();
                gameState.newGame = true;
            }
            Menu.Run(&gameState);
            Player.ResetState();

        }
    }
}

void Game::Render(Player& Player, sf::RenderWindow* window)
{
    window->clear(sf::Color::White);
    window->draw(_skySprite);
    Player.Draw(window);

    window->draw(_scoreText);

    for (auto &bulletIterator : _bulletList)
    {
        bulletIterator->Draw(window);
    }

    for (auto &enemyIterator : _enemyList)
    {
        enemyIterator->Draw(window);
    }

    for (auto &explosionIterator : _explosionList)
    {
        explosionIterator->Draw(window);
    }

    for (auto &coinIterator : _coinList)
    {
        coinIterator->Draw(window);
    }

    window->display();
}

void Game::ResetGame(Player& Player)
{
    while (_bulletList.size())
    {
        _bulletList.erase(_bulletList.begin());
    }

    while (_explosionList.size())
    {
        _explosionList.erase(_explosionList.begin());
    }

    while (_enemyList.size())
    {
        _enemyList.erase(_enemyList.begin());
    }

    while (_coinList.size())
    {
        _coinList.erase(_coinList.begin());
    }

    Player.ResetLives();
    _gameState->gameOver = false;
    _score = 0;
}

void Game::UpdateHighScore(void)
{
    if (_score > _highScore)
    {
        _highScore = _score;
        _gameState->highScore = _highScore;
    }
}

bool Game::IsGameOver(Player &Player)
{
    if (Player.GetLivesCount() < 1)
    {
        _gameState->gameOver = true;
        return true;
    }

    return false;
}

void Game::UpdateLevel()
{
    _currentLevel = LevelManager::GetLevel(_score);
}

void Game::HandleBullets(Player& Player, sf::Time TimePerFrame)
{
    for (auto &bulletIterator : _bulletList)
    {
        bulletIterator->Update(TimePerFrame, _currentLevel);
    }

    if(Player.IsTriggerPressed())
    {
        std::unique_ptr<Bullet> BulletPtr = std::make_unique<Bullet>();
        BulletPtr->SetPosition(Player.GetPosition());
        BulletPtr->SetOwner(PLAYERS_BULLET);
        _bulletList.emplace_back(std::move(BulletPtr));
        Player.BulletFired();
    }

    for (auto &enemyIterator : _enemyList)
    {
        if (enemyIterator->Fire())
        {
            std::unique_ptr<Bullet> BulletPtr = std::make_unique<Bullet>();
            BulletPtr->SetPosition(enemyIterator->GetPosition());
            BulletPtr->SetOwner(ENEMYS_BULLET);
            _bulletList.emplace_back(std::move(BulletPtr));
            enemyIterator->HasFired();
        }
    }

    for(size_t i = 0; i < _bulletList.size(); i++)
    {
        if (_bulletList[i]->GetPosition().x >= _viewSize.x || _bulletList[i]->GetPosition().x < 0)
        {
            _bulletList.erase(_bulletList.begin() + i);
        }
    }

    HandlePlayerBulletCollison(Player);
}

void Game::HandlePlayerBulletCollison(Player& Player)
{
    for (size_t i = 0; i < _bulletList.size(); i++)
    {
        if(CheckCollision(_bulletList[i]->GetSprite(), Player.GetSprite()) && _bulletList[i]->GetOwner() == ENEMYS_BULLET)
        {
            //Reduce player's life
            Player.ReduceLife();
            _bulletList.erase(_bulletList.begin() + i);
        }
    }
}

void Game::HandleCoins(Player& Player)
{
    HandlePlayerCoinCollision(Player);
    SpawnCoins();
}

void Game::SpawnCoins(void)
{
    static size_t millis, diff;

    static bool clockStarted = false;
    bool spawn = false;
    static std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

    if (!clockStarted)
    {
        startTime = std::chrono::system_clock::now();
        clockStarted = true;

        std::random_device rd;
        std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> distribution(5000, 10000);
        millis = distribution(gen);
    }

    endTime = std::chrono::system_clock::now();

    diff = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();


    if (diff >= millis)
    {
        clockStarted = false;
        spawn = true;
    }

    if (spawn && (_coinList.size() < GetValue(MEDAL_COUNT, _currentLevel)))
    {
        spawn = false;
        std::unique_ptr<Coin> CoinPtr = std::make_unique<Coin>(_viewSize);
        _coinList.push_back(std::move(CoinPtr));
    }
}

void Game::HandlePlayerCoinCollision(Player& Player)
{
    for (uint8_t i = 0; i < _coinList.size(); i++)
    {
        if (CheckCollision(_coinList[i]->GetSprite(), Player.GetSprite()))
        {
            //Check coin type and increase the SCORE
            Player.PlayCoinSound();

            if (_coinList[i]->GetCoinType() == SILVER_COIN)
            {
                 _score += 2;
                 Player.IncreaseSpeed();
            }
            else if (_coinList[i]->GetCoinType() == GOLD_COIN)
            {
                _score += 3;
                Player.IncreaseLife();
            }

            _coinList.erase(_coinList.begin() + i);
        }
    }
}

void Game::HandleEnemy(sf::Time TimePerFrame, Player& Player)
{
    for (auto &enemyIterator : _enemyList)
    {
        enemyIterator->Update(TimePerFrame, Player.GetPosition(), _currentLevel);
    }

    SpawnEnemy();

    HandlePlayerEnemyCollision(Player);
    HandleEnemyBulletCollision();

    for (size_t i = 0; i < _enemyList.size(); i++)
    {
        if (_enemyList[i]->GetPosition().x < 0)
        {
            _enemyList.erase(_enemyList.begin() + i);
            Player.ReduceLife();
        }
    }


    CheckEnemyLives();
}

void Game::SpawnEnemy(void)
{
    static size_t millis, diff;
    int min = 0, max = 0;

    static bool clockStarted = false;
    bool spawn = false;
    static std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

    if (!clockStarted)
    {
        startTime = std::chrono::system_clock::now();
        clockStarted = true;

        min = GetValue(ENEMY_SPAWN_MIN, _currentLevel);
        max = GetValue(ENEMY_SPAWN_MAX, _currentLevel);

        std::random_device rd;
        std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> distribution(min, max);
        millis = distribution(gen);
    }

    endTime = std::chrono::system_clock::now();

    diff = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    if (diff >= millis)
    {
        clockStarted = false;
        spawn = true;
    }

    if (spawn && (_enemyList.size() < GetValue(ENEMY_COUNT, _currentLevel)))
    {
        spawn = false;
        std::unique_ptr<Enemy> EnemytPtr = std::make_unique<Enemy>(_viewSize);
        _enemyList.emplace_back(std::move(EnemytPtr));
    }
}

void Game::HandleEnemyBulletCollision(void)
{
    for (size_t i = 0; i < _bulletList.size(); i++)
    {
        for (size_t j = 0; j < _enemyList.size(); j++)
        {
            if ( CheckCollision(_bulletList[i]->GetSprite(), _enemyList[j]->GetSprite()) && (_bulletList[i]->GetOwner() == PLAYERS_BULLET) )
            {
                _score++;
                //_bulletList.erase(_bulletList.begin() + i);
                _bulletList[i]->Invalidate();
                _enemyList[j]->ReduceLife();
            }
        }
    }
}

void Game::CheckEnemyLives(void)
{
    for (size_t i = 0; i < _enemyList.size(); i++)
    {
        if (_enemyList[i]->GetLivesCount() <= 0)
        {
            AddExplosion(_enemyList[i]->GetSprite().getGlobalBounds());
            _enemyList.erase(_enemyList.begin() + i);
        }
    }
}

void Game::HandlePlayerEnemyCollision(Player& Player)
{
    for (size_t i = 0; i < _enemyList.size(); i++)
    {
        if (CheckCollision(_enemyList[i]->GetSprite(), Player.GetSprite()))
        {
            //Reduce player's life
            Player.ReduceLife();
            AddExplosion(_enemyList[i]->GetSprite().getGlobalBounds());
            _enemyList.erase(_enemyList.begin() + i);
        }
    }
}

void Game::AddExplosion(sf::FloatRect rect)
{
    sf::Vector2f position;

    position.x = (rect.left);
    position.y = (rect.top);

    std::unique_ptr<Explosion> ExplosiontPtr = std::make_unique<Explosion>(position);
    _explosionList.push_back(std::move(ExplosiontPtr));
}

void Game::HandleExplosion(void)
{
    for (size_t i = 0; i < _explosionList.size(); i++)
    {
        if (_explosionList[i]->IsExplodeComplete())
        {
            _explosionList.erase(_explosionList.begin() + i);
        }
    }
}

bool Game::CheckCollision(sf::Sprite sprite1, sf::Sprite sprite2)
{
    sf::FloatRect shape1 = sprite1.getGlobalBounds();
    sf::FloatRect shape2 = sprite2.getGlobalBounds();

    return shape1.intersects(shape2);
}

void Game::SetScoreAndLives(Player& Player)
{
    _scoreText.setString("Lives: " + std::to_string(Player.GetLivesCount()) + "  Score: " + std::to_string(_score));
}

