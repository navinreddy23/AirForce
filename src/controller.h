#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

typedef enum
{
    NOTHING_PRESSED,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_SPACE,
    KEY_ESCAPE
} keys_t;

class Controller
{
public:
    Controller();
    keys_t HandleInput(sf::RenderWindow* window);
};

#endif // CONTROLLER_H
