#include "stdafx.h"
#include "Missile.h"
#include "Game.h"

static unsigned int identifier = 0;

Missile::Missile(sf::Vector2f velocity, float x, float y) :
CircleShape(3),
velocity(velocity.x, 0),
id(identifier++)
{
    setPosition(x + 10, y);
    setFillColor(sf::Color(255, 255, 255, 255));
}

Missile::~Missile()
{
}

void Missile::Update(float elapsedTime)
{
    velocity.x += 1000;
    velocity.x *= elapsedTime;

    sf::Color color = getFillColor();
    color.a -=100;
    setFillColor(color);

    move(velocity);
}

unsigned int Missile::Id()
{
    return id;
}