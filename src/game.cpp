#include "game.h"
#include "controller.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"

#include <iostream>
#include <memory>

#define RESOLUTION_X 1280
#define RESOLUTION_Y 720

Game::Game()
{
    viewSize.x = RESOLUTION_X;
    viewSize.y = RESOLUTION_Y;

    vm.width = viewSize.x;
    vm.height = viewSize.y;

    window.create(vm, "AirForceClass");

    skyTexture.loadFromFile("../Assets/Graphics/Background_1.png");
    skySprite.setTexture(skyTexture);
}

void Game::Run(void)
{
    Controller Controller;
    Player Player(viewSize);

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    auto TimePerFrame =  sf::seconds(1.f / FPS);

    while (window.isOpen())
    {
        //Controller.HandleInput(&window);
        Player.Update(Controller.HandleInput(&window), TimePerFrame);

        // Update Game
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            Player.Update(Controller.HandleInput(&window), TimePerFrame);
            HandlePlayerBullet(&Player, TimePerFrame);
            HandleEnemy();
            HandleExplosion();

            //update(TimePerFrame);
            //std::cout << "Time since last update(0): " << timeSinceLastUpdate.asMilliseconds() << std::endl;
        }

        //Render
        Render(&Player);
        //Enemy.Draw(&window);
    }
}

void Game::Render(Player *Player)
{
    window.clear(sf::Color::White);
    window.draw(skySprite);
    Player->Draw(&window);

    //std::cout << "Size of vector: " << bulletVec.size() << std::endl;
    for (auto &bulletIterator : bulletList)
    {
        bulletIterator->Draw(&window);
    }

    for (auto &enemyIterator : enemyList)
    {
        enemyIterator->Draw(&window);
    }

    for (auto &explosionIterator : explosionList)
    {
        explosionIterator->Draw(&window);
    }

    window.display();
}

void Game::HandlePlayerBullet(Player* Player, sf::Time TimePerFrame)
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

    for(size_t i = 0; i < bulletList.size(); i++)
    {
        if (bulletList[i]->GetPosition().x >= viewSize.x)
        {
            bulletList.erase(bulletList.begin() + i);
        }
    }
}

void Game::HandleEnemy()
{
    if (enemyList.size() == 0 && enemyList.size() < 2)
    {
        std::unique_ptr<Enemy> EnemytPtr = std::make_unique<Enemy>(viewSize);
        enemyList.push_back(std::move(EnemytPtr));
    }

    if (bulletList.size() > 0 && enemyList.size() > 0)
    {
        //std::cout << "BulletList Size: " << bulletList.size() << " EnemyList Size: " << enemyList.size() << std::endl;
        HandleEnemyBulletCollision();
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

void Game::AddExplosion(sf::FloatRect rect)
{
    //std::cout << "Explosion position      X: " << position.x << " Y: " << position.y << std::endl;
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
