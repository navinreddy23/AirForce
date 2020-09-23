#include "controller.h"


Controller::Controller(void)
{

}

keys_t Controller::HandleInput(sf::RenderWindow *window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Right)
              return KEY_RIGHT_PRESS;

            if(event.key.code == sf::Keyboard::Left)
               return KEY_LEFT_PRESS;

            if(event.key.code == sf::Keyboard::Up)
               return KEY_UP_PRESS;

            if(event.key.code == sf::Keyboard::Down)
               return KEY_DOWN_PRESS;

            if(event.key.code == sf::Keyboard::Space)
               return KEY_SPACE;

            if(event.key.code == sf::Keyboard::P)
               return KEY_PAUSE_PRESS;

            if(event.key.code == sf::Keyboard::Enter)
               return KEY_ENTER_PRESS;

            if (event.key.code == sf::Keyboard::Escape)
                return KEY_ESCAPE_PRESS;
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::Right)
              return KEY_RIGHT_RELEASE;

            if(event.key.code == sf::Keyboard::Left)
               return KEY_LEFT_RELEASE;

            if(event.key.code == sf::Keyboard::Up)
               return KEY_UP_RELEASE;

            if(event.key.code == sf::Keyboard::Down)
               return KEY_DOWN_RELEASE;

            if(event.key.code == sf::Keyboard::Enter)
               return KEY_ENTER_RELEASE;
        }
        else if(event.type == sf::Event::Closed)
        {
            window->close();
        }
        else
        {
            return NOTHING_PRESSED;
        }
    }
    return NOTHING_PRESSED;
}
