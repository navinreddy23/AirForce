#include "game.h"
#include "controller.h"
#include "player.h"
#include "bullet.h"

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

    skyTexture.loadFromFile("../Assets/Graphics/Background.png");
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
            HandlePlayerBullet(&Player);
            for (auto &bulletIterator : bulletVec)
            {
                bulletIterator->Update(TimePerFrame);
            }
            //update(TimePerFrame);
            //std::cout << "Time since last update(0): " << timeSinceLastUpdate.asMilliseconds() << std::endl;
        }

        //Render
        Render(&Player);
    }
}

void Game::Render(Player *Player)
{
    window.clear(sf::Color::White);
    window.draw(skySprite);
    Player->Draw(&window);

    //std::cout << "Size of vector: " << bulletVec.size() << std::endl;
    for (auto &bulletIterator : bulletVec)
    {
        bulletIterator->Draw(&window);
    }
    window.display();
}

void Game::HandlePlayerBullet(Player* Player)
{
    if(Player->IsTriggerPressed())
    {
        std::unique_ptr<Bullet> BulletPtr = std::make_unique<Bullet>();
        BulletPtr->SetPosition(Player->GetPosition());
        BulletPtr->SetOwner(PlayersBullet);
        bulletVec.push_back(std::move(BulletPtr));
        Player->BulletFired();
    }

    for(size_t i = 0; i < bulletVec.size(); i++)
    {
        if (bulletVec[i]->GetPosition().x >= viewSize.x)
        {
            bulletVec.erase(bulletVec.begin() + i);
        }
    }
}
