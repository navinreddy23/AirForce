#include "controller.h"


Controller::Controller()
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
              return KEY_RIGHT;

            if(event.key.code == sf::Keyboard::Left)
               return KEY_LEFT;

            if(event.key.code == sf::Keyboard::Up)
               return KEY_UP;

            if(event.key.code == sf::Keyboard::Down)
               return KEY_DOWN;

            if(event.key.code == sf::Keyboard::Space)
               return KEY_SPACE;

            if (event.key.code == sf::Keyboard::Escape)
                window->close();
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
