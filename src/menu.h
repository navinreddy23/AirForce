#ifndef MENU_H
#define MENU_H

#include "game.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

typedef enum
{
    MENU_OUTER_INITIAL,
    MENU_OUTER_PAUSE,
    MENU_INNER_INSTR,
    MENU_INNER_HIGHSCORE,
    MENU_GAMEOVER
}menu_state_t;

typedef enum
{
    CONTINUE,
    NEW_GAME,
    INSTRUCTIONS,
    HIGH_SCORE,
    EXIT_GAME,
    BUTTONS_SIZE
}menu_buttons_t;

class Menu
{
public:
    Menu(sf::RenderWindow* window, sf::Vector2f _viewSize);
    ~Menu();
    void Run(interface_t *gameState);

private:
    void LoadSprites(void);
    void LoadFonts(void);
    void Render(void);
    void HandleInput(keys_t key);
    void SetCurrentButton();
    void DrawMenu(void);
    void ExecuteItem(keys_t key);
    void UpdateHighScore(void);

    sf::RenderWindow* _window;

    sf::Vector2f _viewSize;

    menu_buttons_t _currentButton;
    menu_state_t _menuState = MENU_OUTER_INITIAL;

    int _itemIndex = 0;

    bool _exitMenu;

    interface_t* _gameState;

    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;

    sf::Texture _menuTexture;
    sf::Sprite  _menuSprite;

    sf::Font _gameFont;
    sf::Text _gameNameText;

    std::vector <sf::Text> _menuText;
    std::vector <std::string> _menuString = {"CONTINUE", "NEW GAME", "INSTRUCTIONS", "HIGH SCORE", "EXIT GAME"};

    sf::Text _highScoreText;
    std::string _highScoreString;

    sf::Text _gameOverText;

    sf::Text _instructionText;
    std::string _instructionString;
};

#endif // MENU_H
