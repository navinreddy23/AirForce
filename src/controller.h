#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

typedef enum
{
    NOTHING_PRESSED,
    KEY_UP_PRESS,
    KEY_DOWN_PRESS,
    KEY_LEFT_PRESS,
    KEY_RIGHT_PRESS,
    KEY_UP_RELEASE,
    KEY_DOWN_RELEASE,
    KEY_LEFT_RELEASE,
    KEY_RIGHT_RELEASE,
    KEY_PAUSE_PRESS,
    KEY_ENTER_PRESS,
    KEY_ENTER_RELEASE,
    KEY_SPACE,
    KEY_ESCAPE_PRESS
} keys_t;

class Controller
{
public:
    Controller(void);
    keys_t HandleInput(sf::RenderWindow* window);
};

#endif // CONTROLLER_H
