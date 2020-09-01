#include "game.h"
#include "controller.h"
#include "player.h"
#include <iostream>

Game::Game()
{
    viewSize.x = 1280;
    viewSize.y = 720;

    //Unnnecessary
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
    window.display();
}
