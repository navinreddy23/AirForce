#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

#define SCALE_HERO 0.36
#define MOVE_DISTANCE 300.0f

sf::Vector2f viewSize(1280, 720);
sf::Vector2f playerPosition;
bool playerMovingRight, playerMovingLeft, playerMovingUp, playerMovingDown;

sf::VideoMode vm(viewSize.x, viewSize.y);

sf::RenderWindow window(vm, "AirForce");

sf::Texture skyTexture, heroTexture1, heroTexture2;
sf::Sprite skySprite, heroSprite1, heroSprite2;

void init()
{
    skyTexture.loadFromFile("../Assets/Graphics/Background.png");
    skySprite.setTexture(skyTexture);

    heroTexture1.loadFromFile("../Assets/Graphics/Plane/Fly_1.png");
    heroSprite1.setTexture(heroTexture1);
    heroTexture1.setSmooth(true);
    heroSprite1.scale(SCALE_HERO, SCALE_HERO);
    heroSprite1.setPosition(sf::Vector2f(viewSize.x / 2 , viewSize.y / 2 ));
    heroSprite1.setOrigin(heroTexture1.getSize().x / 2, heroTexture1.getSize().y / 2);

    heroTexture2.loadFromFile("../Assets/Graphics/Plane/Fly_2.png");
    heroSprite2.setTexture(heroTexture2);
    heroTexture2.setSmooth(true);
    heroSprite2.scale(SCALE_HERO, SCALE_HERO);
    heroSprite2.setPosition(sf::Vector2f(viewSize.x / 2 , viewSize.y / 2 ));
    heroSprite2.setOrigin(heroTexture2.getSize().x / 2, heroTexture2.getSize().y / 2);


}

void draw(sf::Time time)
{
    static int count = 0;
    static float prevTime = 0;
    if(prevTime != time.asMilliseconds())
    {
        count++;
    }
    window.draw(skySprite);

    std::cout << "Time since last update(1): " << time.asMilliseconds() << std::endl;

    if(count <= 1)
    {
         window.draw(heroSprite1);
    }
    else if(count == 2)
    {
         window.draw(heroSprite2);
         count = 0;
    }

    prevTime = time.asMilliseconds();

}

void update(sf::Time time)
{
    float dt = time.asSeconds();
    if (playerMovingRight)
    {
        heroSprite1.move(MOVE_DISTANCE * dt, 0);
        heroSprite2.move(MOVE_DISTANCE * dt, 0);
    }
    else if (playerMovingLeft)
    {
        heroSprite1.move(-MOVE_DISTANCE * dt, 0);
        heroSprite2.move(-MOVE_DISTANCE * dt, 0);
    }
    else if (playerMovingUp)
    {
        heroSprite1.move(0, -MOVE_DISTANCE * dt);
        heroSprite2.move(0, -MOVE_DISTANCE * dt);
    }
    else if (playerMovingDown)
    {
        heroSprite1.move(0, MOVE_DISTANCE * dt);
        heroSprite2.move(0, MOVE_DISTANCE * dt);
    }

 std::cout << dt << std::endl;
}

void updateInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Right)
               playerMovingRight = true;

            if(event.key.code == sf::Keyboard::Left)
               playerMovingLeft = true;

            if(event.key.code == sf::Keyboard::Up)
               playerMovingUp = true;

            if(event.key.code == sf::Keyboard::Down)
               playerMovingDown = true;

            if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
                window.close();
        }

        if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code == sf::Keyboard::Right)
                playerMovingRight = false;

            if(event.key.code == sf::Keyboard::Left)
               playerMovingLeft = false;

            if(event.key.code == sf::Keyboard::Up)
               playerMovingUp = false;

            if(event.key.code == sf::Keyboard::Down)
               playerMovingDown = false;
        }
    }
}

int main()
{
    init();
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    auto TimePerFrame =  sf::seconds(1.f / 60.f);

    while (window.isOpen())
    {
        updateInput();

        // Update Game
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            updateInput();
            update(TimePerFrame);
            std::cout << "Time since last update(0): " << timeSinceLastUpdate.asMilliseconds() << std::endl;
        }

        //Render
        window.clear(sf::Color::White);
        draw(timeSinceLastUpdate);
        window.display();
    }

    return 0;
}
