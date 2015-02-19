#include "stdafx.h"
#include "Spaceship.h"
#include "Missile.h"
#include "Game.h"

#define MOVE_VELOCITY 400

Spaceship::Spaceship() : 
velocity(0,0)
{
    texture.loadFromFile("viper.png");
    setTexture(texture);
    setPosition(300, 300);
}

Spaceship::~Spaceship()
{
}

void Spaceship::Update(float elapsedTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x -= MOVE_VELOCITY;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        velocity.y -= MOVE_VELOCITY;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x += MOVE_VELOCITY;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        velocity.y += MOVE_VELOCITY;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        FireMissile();

    velocity.x *= elapsedTime;
    velocity.y *= elapsedTime;

    move(velocity);

    float x = getPosition().x;
    float y = getPosition().y;
    if (x < 0)
        x = 0;
    if (x > 1024)
        x = 1024;
    if (y < 0)
        y = 0;
    if (y > 768)
        y = 768;

    setPosition(x, y);

    if (missile)
        missile->Update(elapsedTime);
}

void Spaceship::FireMissile()
{
    // Throttle fire speed
    if (clock.getElapsedTime().asMilliseconds() > 200)
        clock.restart();
    else
        return;

    float x = getPosition().x;
    float y = getPosition().y;

    x += getLocalBounds().width / 2;
    y += getLocalBounds().height / 2;

   Game::get().AddMissile(std::shared_ptr<Missile>(new Missile(velocity, x, y)));
}
