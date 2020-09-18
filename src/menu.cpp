#include "menu.h"
#include "controller.h"
#include <iostream>

//Menu::Menu()
//{
//    LoadSprites();
//}

Menu::Menu(sf::RenderWindow* window, sf::Vector2f viewSize) : _window(window), _viewSize(viewSize)
{
    LoadSprites();
    LoadFonts();
}

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
    menuSprite.setPosition(sf::Vector2f( _viewSize.x / 2, _viewSize.y / 2 ));
    menuSprite.setOrigin(menuTexture.getSize().x / 2, menuTexture.getSize().y / 2);

    std::cout << "Menu: Sprites loaded" << std::endl;
}

void Menu::LoadFonts()
{
    gameFont.loadFromFile("../Assets/Fonts/Font.ttf");

    gameNameText.setFont(gameFont);
    gameNameText.setString("Air Force");
    gameNameText.setCharacterSize(125);
    gameNameText.setFillColor(sf::Color::White);

    gameNameText.setPosition(sf::Vector2f(_viewSize.x * 0.5, _viewSize.y * 0.1));

    sf::FloatRect headingbounds = gameNameText.getLocalBounds();
    //gameNameText.setOrigin(_viewSize.x / 2, _viewSize.y / 2);
    gameNameText.setOrigin(headingbounds.width / 2, headingbounds.height / 2);
}

void Menu::Run()
{
    Controller Controller;
    keys_t key;

    while (_window->isOpen() && key != KEY_PAUSE_PRESS)
    {
        key = Controller.HandleInput(_window);
        Render();
    }

    Game::pause = false;
}

void Menu::Render()
{
    _window->clear(sf::Color::White);
    _window->draw(bgSprite);
    _window->draw(menuSprite);
    _window->draw(gameNameText);
    _window->display();
}


