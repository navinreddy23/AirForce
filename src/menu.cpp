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
    gameNameText.setOrigin(headingbounds.width / 2, headingbounds.height / 2);


    highScoreText.setFont(gameFont);
    highScoreString = "Highscore: 0";
    highScoreText.setString(highScoreString);
    highScoreText.setCharacterSize(75);
    highScoreText.setFillColor(sf::Color::White);

    highScoreText.setPosition(sf::Vector2f(_viewSize.x * 0.5, _viewSize.y * 0.5));

    sf::FloatRect scoreBound = highScoreText.getLocalBounds();
    highScoreText.setOrigin(scoreBound.width / 2, scoreBound.height / 2);

    instructionText.setFont(gameFont);
    instructionString = "Use ARROW keys to move the aircraft.\nDestroy the enemy aircrafts, "
                        "use SPACE to fire the bullets.\nUse the three lives to beat your previous highscore!";
    instructionText.setString(instructionString);
    instructionText.setCharacterSize(30);
    instructionText.setFillColor(sf::Color::White);

    instructionText.setPosition(sf::Vector2f(_viewSize.x * 0.4, _viewSize.y * 0.4));

    sf::FloatRect instBound = highScoreText.getLocalBounds();
    instructionText.setOrigin(instBound.width / 2, instBound.height / 2);


    menuText.resize(BUTTONS_SIZE);

    for (int i = 0; i < BUTTONS_SIZE; i++)
    {
        menuText[i].setFont(gameFont);
        menuText[i].setString(menuString[i]);
        menuText[i].setCharacterSize(50);

        menuText[i].setFillColor(sf::Color::White);

        menuText[i].setPosition(sf::Vector2f(_viewSize.x * 0.5, (_viewSize.y * (0.3 + i*0.1)  )));

        sf::FloatRect bounds = menuText[i].getLocalBounds();
        menuText[i].setOrigin(bounds.width / 2, bounds.height / 2);
    }
}

void Menu::Run(interface_t* gameState)
{
    Controller Controller;
    keys_t key;

    _gameState = gameState;

    exitMenu = false;

    index = NEW_GAME;

    if (!_gameState->showInitMenu)
    {
        menuState = MENU_OUTER_PAUSE;
        index = CONTINUE;
        UpdateHighScore();
    }

    while (_window->isOpen() && !exitMenu)
    {
        key = Controller.HandleInput(_window);
        HandleInput(key);
        Render();
    }

    gameState->pause = false;
}

void Menu::HandleInput(keys_t key)
{
    if(key == KEY_UP_RELEASE)
    {
        index--;
    }
    else if (key == KEY_DOWN_RELEASE)
    {
        index++;
    }

    if (_gameState->showInitMenu && index > EXIT_GAME)
    {
        index = NEW_GAME;
    }
    else if (!_gameState->showInitMenu && index > EXIT_GAME)
    {
        index = CONTINUE;
    }

    if(index < 0)
    {
        index = EXIT_GAME;
    }

    SetCurrentButton();
    ExecuteItem(key);
}

void Menu::ExecuteItem(keys_t key)
{
    if (key == KEY_ENTER_PRESS)
    {
        switch (index)
        {
        case CONTINUE:
            exitMenu = true;
            break;
        case NEW_GAME:
            _gameState->newGame = true;
            exitMenu = true;
            break;
        case EXIT_GAME:
            _window->close();
            break;
         case HIGH_SCORE:
            menuState = MENU_INNER_HIGHSCORE;
            break;
        case INSTRUCTIONS:
            menuState = MENU_INNER_INSTR;
            break;
        }
    }
    else if(key == KEY_ESCAPE_PRESS)
    {   if (menuState == MENU_OUTER_PAUSE)
            exitMenu = true;
        else if(!(_gameState->showInitMenu))
            menuState = MENU_OUTER_PAUSE;
        else if(_gameState->showInitMenu)
            menuState = MENU_OUTER_INITIAL;
    }
}

void Menu::SetCurrentButton()
{
     menuText[index].setFillColor(sf::Color::Cyan);

    for (int i = CONTINUE; i < BUTTONS_SIZE; i++)
    {
        if (i != index)
        {
            menuText[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::Render()
{
    _window->clear(sf::Color::White);
    _window->draw(bgSprite);
    _window->draw(menuSprite);
    _window->draw(gameNameText);

    DrawMenu();

    _window->display();
}

void Menu::DrawMenu()
{
    switch (menuState)
    {
    case MENU_OUTER_INITIAL:
        for (int i = NEW_GAME; i < BUTTONS_SIZE; i++)
            _window->draw(menuText[i]);
        break;
    case  MENU_OUTER_PAUSE:
        for (int i = CONTINUE; i < BUTTONS_SIZE; i++)
            _window->draw(menuText[i]);
        break;
    case  MENU_INNER_INSTR:
        _window->draw(instructionText);
        break;
    case  MENU_INNER_HIGHSCORE:
        _window->draw(highScoreText);
        break;
    }
}

void Menu::UpdateHighScore()
{
    highScoreString = "High Score:  " + std::to_string(_gameState->highScore);
    highScoreText.setString(highScoreString);
}


