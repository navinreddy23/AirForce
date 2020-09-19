#include "game.h"
#include "controller.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "menu.h"

#include <iostream>
#include <memory>
#include <chrono>
#include <random>

#define RESOLUTION_X 1280
#define RESOLUTION_Y 720

#define SCALE_BACKGROUND 1

#define FPS 60.0F


Game::Game()
{

}

void Game::Init(sf::RenderWindow* window)
{
    viewSize.x = RESOLUTION_X;
    viewSize.y = RESOLUTION_Y;

    vm.width = viewSize.x;
    vm.height = viewSize.y;

    window->create(vm, "AirForce");

    skyTexture.loadFromFile("../Assets/Graphics/Background_1.png");

    skySprite.setTexture(skyTexture);
    skyTexture.setSmooth(true);
    skySprite.scale(1, 0.75);
}

void Game::Run(void)
{
    sf::RenderWindow window;

    Init(&window);

    interface_t gameState;

    Menu Menu(&window, viewSize);
    Controller Controller;
    Player Player(viewSize);

    gameState.showInitMenu = true;
    Menu.Run(&gameState);
    gameState.showInitMenu = false;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    auto TimePerFrame =  sf::seconds(1.f / FPS);

    while (window.isOpen())
    {
        //Game::score = 24;
        SetScore(24);
        keys_t key = Controller.HandleInput(&window);

        if (pause)
        {
            Menu.Run(&gameState);
            pause = false;
        }

        if (gameState.newGame)
        {
            ResetGame();
            //Reset complete
            gameState.newGame = false;
        }


        if (!pause) Player.Update(key, TimePerFrame);

        if (key == KEY_ESCAPE_PRESS)
        {
            std::cout << "Pause" << std::endl;
            pause = !pause;
        }

        // Update Game
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            if(pause) break;

            Player.Update(Controller.HandleInput(&window), TimePerFrame);

            HandleBullets(&Player, TimePerFrame);
            HandleEnemy(TimePerFrame, Player);
            HandleExplosion();

            //update(TimePerFrame);
            //std::cout << "Time since last update(0): " << timeSinceLastUpdate.asMilliseconds() << std::endl;
        }

        //Render
        if(!pause) Render(&Player, &window);
        //Enemy.Draw(&window);
    }
}

void Game::Render(Player *Player, sf::RenderWindow* window)
{
    window->clear(sf::Color::White);
    window->draw(skySprite);
    Player->Draw(window);

    //std::cout << "Size of vector: " << bulletVec.size() << std::endl;
    for (auto &bulletIterator : bulletList)
    {
        bulletIterator->Draw(window);
    }

    for (auto &enemyIterator : enemyList)
    {
        enemyIterator->Draw(window);
    }

    for (auto &explosionIterator : explosionList)
    {
        explosionIterator->Draw(window);
    }

    window->display();
}

void Game::ResetGame()
{
    while (bulletList.size())
    {
        bulletList.erase(bulletList.begin());
    }

    while (explosionList.size())
    {
        explosionList.erase(explosionList.begin());
    }

    while (enemyList.size())
    {
        enemyList.erase(enemyList.begin());
    }
}

void Game::HandleBullets(Player* Player, sf::Time TimePerFrame)
{
    for (auto &bulletIterator : bulletList)
    {
        bulletIterator->Update(TimePerFrame);
    }

    if(Player->IsTriggerPressed())
    {
        std::unique_ptr<Bullet> BulletPtr = std::make_unique<Bullet>();
        BulletPtr->SetPosition(Player->GetPosition());
        BulletPtr->SetOwner(PlayersBullet);
        bulletList.push_back(std::move(BulletPtr));
        Player->BulletFired();
    }

    for (auto &enemyIterator : enemyList)
    {
        if (enemyIterator->Fire())
        {
            std::unique_ptr<Bullet> BulletPtr = std::make_unique<Bullet>();
            BulletPtr->SetPosition(enemyIterator->GetPosition());
            BulletPtr->SetOwner(EnemiesBullet);
            bulletList.push_back(std::move(BulletPtr));
            enemyIterator->HasFired();
        }
    }

    for(size_t i = 0; i < bulletList.size(); i++)
    {
        if (bulletList[i]->GetPosition().x >= viewSize.x || bulletList[i]->GetPosition().x < 0)
        {
            bulletList.erase(bulletList.begin() + i);
        }
    }

    HandlePlayerBulletCollison(Player);
}

void Game::HandlePlayerBulletCollison(Player* Player)
{
    for (uint8_t i = 0; i < bulletList.size(); i++)
    {
        if(CheckCollision(bulletList[i]->GetSprite(), Player->GetSprite()) && bulletList[i]->GetOwner() == EnemiesBullet)
        {
            //Reduce player's life
            AddExplosion(Player->GetSprite().getGlobalBounds());
            bulletList.erase(bulletList.begin() + i);
        }
    }
}

void Game::HandleEnemy(sf::Time TimePerFrame, Player& Player)
{
    for (auto &enemyIterator : enemyList)
    {
        enemyIterator->Update(TimePerFrame, Player.GetPosition());
    }

    SpawnEnemy();


    if (bulletList.size() > 0 && enemyList.size() > 0)
    {
        //std::cout << "BulletList Size: " << bulletList.size() << " EnemyList Size: " << enemyList.size() << std::endl;
        HandleEnemyBulletCollision();
    }

    for(size_t i = 0; i < enemyList.size(); i++)
    {
        if (enemyList[i]->GetPosition().x < 0)
        {
            enemyList.erase(enemyList.begin() + i);
        }
    }

    HandlePlayerEnemyCollision(Player);
}

void Game::SpawnEnemy(void)
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
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribution(1500, 2000);
        millis = distribution(gen);
    }

    endTime = std::chrono::system_clock::now();

    diff = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();


    if (diff >= millis)
    {
        clockStarted = false;
        spawn = true;
    }

    if (spawn && (enemyList.size() < 1))
    {
        spawn = false;
        std::unique_ptr<Enemy> EnemytPtr = std::make_unique<Enemy>(viewSize);
        enemyList.push_back(std::move(EnemytPtr));

    }
}

void Game::HandleEnemyBulletCollision(void)
{
    for (uint32_t i = 0; i < bulletList.size(); i++)
    {
        for (uint8_t j = 0; j < enemyList.size(); j++)
        {
            if(CheckCollision(bulletList[i]->GetSprite(), enemyList[j]->GetSprite()) && bulletList[i]->GetOwner() == PlayersBullet)
            {
                bulletList.erase(bulletList.begin() + i);

                AddExplosion(enemyList[j]->GetSprite().getGlobalBounds());

                enemyList.erase(enemyList.begin() + j);
            }
        }
    }
}

void Game::HandlePlayerEnemyCollision(Player& Player)
{
    for (uint8_t i = 0; i < enemyList.size(); i++)
    {
        if(CheckCollision(enemyList[i]->GetSprite(), Player.GetSprite()))
        {
            //Reduce player's life
            AddExplosion(enemyList[i]->GetSprite().getGlobalBounds());
            enemyList.erase(enemyList.begin() + i);
        }
    }
}

void Game::AddExplosion(sf::FloatRect rect)
{
    sf::Vector2f position;

    position.x = (rect.left);
    position.y = (rect.top);

    std::unique_ptr<Explosion> ExplosiontPtr = std::make_unique<Explosion>(position);
    explosionList.push_back(std::move(ExplosiontPtr));
}

void Game::HandleExplosion()
{
    for(size_t i = 0; i < explosionList.size(); i++)
    {
        if (explosionList[i]->IsExplodeComplete())
        {
            explosionList.erase(explosionList.begin() + i);
        }
    }
}

bool Game::CheckCollision(sf::Sprite sprite1, sf::Sprite sprite2)
{
    sf::FloatRect shape1 = sprite1.getGlobalBounds();
    sf::FloatRect shape2 = sprite2.getGlobalBounds();

    bool retVal;

    if (shape1.intersects(shape2))
    {
        retVal = true;
    }
    else
    {
        retVal = false;
    }

    return retVal;
}

bool Game::GetPauseState()
{
    return pause;
}

bool Game::GetMenuState()
{
    return showInitMenu;
}

int Game::GetScore()
{
    return score;
}

void Game::SetScore(int value)
{
    score = value;
}
