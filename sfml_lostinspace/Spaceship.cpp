#include "stdafx.h"
#include "Spaceship.h"
#include "Missile.h"
#include "Game.h"

#define MOVE_VELOCITY 500

Spaceship::Spaceship() : 
velocity(0,0)
{
    texture.loadFromFile("viper.gif");
    texture.setSmooth(true);
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

    if (missile)
        missile->Update(elapsedTime);
}

void Spaceship::FireMissile()
{
    // Throttle fire speed
    if (clock.getElapsedTime().asMilliseconds() > 100)
        clock.restart();
    else
        return;

    float x = getPosition().x;
    float y = getPosition().y;

    x += getLocalBounds().width / 2;
    y += getLocalBounds().height / 2;

   Game::get().AddMissile(std::shared_ptr<Missile>(new Missile(velocity, x, y)));
}
