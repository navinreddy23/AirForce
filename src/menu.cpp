#include "menu.h"
#include "controller.h"
#include <iostream>

Menu::Menu()
{
    LoadSprites();
}

//Menu::Menu(sf::RenderWindow* window) : _window(window)
//{
//    LoadSprites();
//}

Menu::~Menu()
{

}

void Menu::LoadSprites()
{
    bgTexture.loadFromFile("../Assets/Graphics/Background_1.png");
    bgSprite.setTexture(bgTexture);
    bgTexture.setSmooth(true);
    bgSprite.scale(1, 0.75);

    menuTexture.loadFromFile("../Assets/Graphics/Menu.png");
    menuSprite.setTexture(menuTexture);
    menuTexture.setSmooth(true);
    menuSprite.scale(1, 1);

    std::cout << "Menu: Sprites loaded" << std::endl;
}

void Menu::Run(sf::RenderWindow* windowPtr)
{
//    Controller Controller;
//    keys_t key;

//    while (window->isOpen() && key != KEY_PAUSE_PRESS)
//    {
//        key = Controller.HandleInput(window);
//        Render(window);
//    }

    //Game::pause = false;

//    do
//    {
//        //key = Controller.HandleInput(_window);
//        Render();
//        //std::cout << "Do-While" << std::endl;
//    } while (key != KEY_PAUSE_PRESS);

}

void Menu::Render(sf::RenderWindow* windowPtr)
{
//    window.clear(sf::Color::White);
//    window->draw(bgSprite);
//    window->draw(menuSprite);
//    window->display();
}


