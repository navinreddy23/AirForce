#include "menu.h"
#include "controller.h"

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
    _bgTexture.loadFromFile("../Assets/Graphics/Background_1.png");
    _bgSprite.setTexture(_bgTexture);
    _bgTexture.setSmooth(true);
    _bgSprite.scale(1, 0.75);

    _menuTexture.loadFromFile("../Assets/Graphics/Menu.png");
    _menuSprite.setTexture(_menuTexture);
    _menuTexture.setSmooth(true);
    _menuSprite.scale(1, 1);
    _menuSprite.setPosition(sf::Vector2f( _viewSize.x / 2, _viewSize.y / 2 ));
    _menuSprite.setOrigin(_menuTexture.getSize().x / 2, _menuTexture.getSize().y / 2);

}

void Menu::LoadFonts()
{
    _gameFont.loadFromFile("../Assets/Fonts/Font.ttf");

    _gameNameText.setFont(_gameFont);
    _gameNameText.setString("Air Force");
    _gameNameText.setCharacterSize(125);
    _gameNameText.setFillColor(sf::Color::White);
    _gameNameText.setPosition(sf::Vector2f(_viewSize.x * 0.5, _viewSize.y * 0.1));
    sf::FloatRect headingbounds = _gameNameText.getLocalBounds();
    _gameNameText.setOrigin(headingbounds.width / 2, headingbounds.height / 2);


    _highScoreText.setFont(_gameFont);
    _highScoreString = "Highscore: 0";
    _highScoreText.setString(_highScoreString);
    _highScoreText.setCharacterSize(75);
    _highScoreText.setFillColor(sf::Color::White);
    _highScoreText.setPosition(sf::Vector2f(_viewSize.x * 0.5, _viewSize.y * 0.5));
    sf::FloatRect scoreBound = _highScoreText.getLocalBounds();
    _highScoreText.setOrigin(scoreBound.width / 2, scoreBound.height / 2);

    _gameOverText.setFont(_gameFont);
    _gameOverText.setString("Game over!");
    _gameOverText.setCharacterSize(120);
    _gameOverText.setFillColor(sf::Color::Red);
    _gameOverText.setPosition(sf::Vector2f(_viewSize.x * 0.5, _viewSize.y * 0.45));
    sf::FloatRect textBound = _gameOverText.getLocalBounds();
    _gameOverText.setOrigin(textBound.width / 2, textBound.height / 2);

    _instructionText.setFont(_gameFont);
    _instructionString = "Use ARROW keys to move the aircraft.\nDestroy the enemy aircrafts, "
                        "use SPACE to fire the bullets.\nUse the three lives to beat your previous highscore!";
    _instructionText.setString(_instructionString);
    _instructionText.setCharacterSize(30);
    _instructionText.setFillColor(sf::Color::White);
    _instructionText.setPosition(sf::Vector2f(_viewSize.x * 0.4, _viewSize.y * 0.4));
    sf::FloatRect instBound = _highScoreText.getLocalBounds();
    _instructionText.setOrigin(instBound.width / 2, instBound.height / 2);


    _menuText.resize(BUTTONS_SIZE);

    for (int i = 0; i < BUTTONS_SIZE; i++)
    {
        _menuText[i].setFont(_gameFont);
        _menuText[i].setString(_menuString[i]);
        _menuText[i].setCharacterSize(50);
        _menuText[i].setFillColor(sf::Color::White);
        _menuText[i].setPosition(sf::Vector2f(_viewSize.x * 0.5, (_viewSize.y * (0.3 + i*0.1)  )));
        sf::FloatRect bounds = _menuText[i].getLocalBounds();
        _menuText[i].setOrigin(bounds.width / 2, bounds.height / 2);
    }
}

void Menu::Render()
{
    _window->clear(sf::Color::White);
    _window->draw(_bgSprite);
    _window->draw(_menuSprite);
    _window->draw(_gameNameText);

    DrawMenu();

    _window->display();
}

void Menu::DrawMenu()
{
    switch (_menuState)
    {
    case MENU_OUTER_INITIAL:
        for (int i = NEW_GAME; i < BUTTONS_SIZE; i++)
            _window->draw(_menuText[i]);
        break;
    case  MENU_OUTER_PAUSE:
        for (int i = CONTINUE; i < BUTTONS_SIZE; i++)
            _window->draw(_menuText[i]);
        break;
    case  MENU_INNER_INSTR:
        _window->draw(_instructionText);
        break;
    case  MENU_INNER_HIGHSCORE:
        _window->draw(_highScoreText);
        break;
    case MENU_GAMEOVER:
        _window->draw(_gameOverText);
        break;
    }
}

void Menu::Run(interface_t* gameState)
{
    Controller Controller;
    keys_t key;

    _gameState = gameState;

    _exitMenu = false;

    _itemIndex = NEW_GAME;


    if (gameState->gameOver)
    {
        _menuState = MENU_GAMEOVER;
        _itemIndex = NEW_GAME;
        _gameState->showInitMenu = true;
    }
    else if (!_gameState->showInitMenu)
    {
        _menuState = MENU_OUTER_PAUSE;
        _itemIndex = CONTINUE;
    }

    UpdateHighScore();

    while (_window->isOpen() && !_exitMenu)
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
        _itemIndex--;
    }
    else if (key == KEY_DOWN_RELEASE)
    {
        _itemIndex++;
    }

    if (_gameState->showInitMenu && _itemIndex > EXIT_GAME)
    {
        _itemIndex = NEW_GAME;
    }
    else if (!_gameState->showInitMenu && _itemIndex > EXIT_GAME)
    {
        _itemIndex = CONTINUE;
    }

    if(_itemIndex < 0)
    {
        _itemIndex = EXIT_GAME;
    }

    SetCurrentButton();
    ExecuteItem(key);
}

void Menu::SetCurrentButton()
{
     _menuText[_itemIndex].setFillColor(sf::Color::Cyan);

    for (int i = CONTINUE; i < BUTTONS_SIZE; i++)
    {
        if (i != _itemIndex)
        {
            _menuText[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::ExecuteItem(keys_t key)
{
    if (key == KEY_ENTER_PRESS)
    {
        switch (_itemIndex)
        {
        case CONTINUE:
            _exitMenu = true;
            break;
        case NEW_GAME:
            _gameState->newGame = true;
            _exitMenu = true;
            break;
        case EXIT_GAME:
            _window->close();
            break;
         case HIGH_SCORE:
            _menuState = MENU_INNER_HIGHSCORE;
            break;
        case INSTRUCTIONS:
            _menuState = MENU_INNER_INSTR;
            break;
        }
    }
    else if(key == KEY_ESCAPE_PRESS)
    {   if (_menuState == MENU_GAMEOVER)
            _menuState = MENU_OUTER_INITIAL;
        else if (_menuState == MENU_OUTER_PAUSE)
            _exitMenu = true;
        else if(!(_gameState->showInitMenu))
            _menuState = MENU_OUTER_PAUSE;
        else if(_gameState->showInitMenu)
            _menuState = MENU_OUTER_INITIAL;
    }
}

void Menu::UpdateHighScore()
{
    _highScoreString = "High Score:  " + std::to_string(_gameState->highScore);
    _highScoreText.setString(_highScoreString);
}
