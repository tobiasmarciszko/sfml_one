#include "stdafx.h"
#include "Spaceship.h"

#define MOVE_VELOCITY 500

using namespace sf;

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
    if (Keyboard::isKeyPressed(Keyboard::Left))
        velocity.x -= MOVE_VELOCITY;

    if (Keyboard::isKeyPressed(Keyboard::Up))
        velocity.y -= MOVE_VELOCITY;

    if (Keyboard::isKeyPressed(Keyboard::Right))
        velocity.x += MOVE_VELOCITY;

    if (Keyboard::isKeyPressed(Keyboard::Down))
        velocity.y += MOVE_VELOCITY;
    
    velocity.x *= elapsedTime;
    velocity.y *= elapsedTime;

    move(velocity);
}
