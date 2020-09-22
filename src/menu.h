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

class Menu : private Game
{
public:
    //Menu();
    Menu(sf::RenderWindow* window, sf::Vector2f viewSize);
    ~Menu();
    void Run(interface_t *gameState);

private:
    void LoadSprites();
    void LoadFonts();
    void Render();
    void HandleInput(keys_t key);
    void SetCurrentButton();
    void DrawMenu();
    void ExecuteItem(keys_t key);
    void UpdateHighScore();

    sf::RenderWindow* _window;

    sf::Vector2f _viewSize;

    menu_buttons_t currentButton;
    menu_state_t menuState = MENU_OUTER_INITIAL;

    int index = 0;

    bool exitMenu;

    interface_t* _gameState;

    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    sf::Texture menuTexture;
    sf::Sprite  menuSprite;

    sf::Font gameFont;
    sf::Text gameNameText;

    std::vector <sf::Text> menuText;
    std::vector <std::string> menuString = {"CONTINUE", "NEW GAME", "INSTRUCTIONS", "HIGH SCORE", "EXIT GAME"};

    sf::Text highScoreText;
    std::string highScoreString;

    sf::Text gameOverText;

    sf::Text instructionText;
    std::string instructionString;


};

#endif // MENU_H
