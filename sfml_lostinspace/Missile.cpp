#include "stdafx.h"
#include "Missile.h"
#include "Game.h"

static unsigned int identifier = 0;

Missile::Missile(sf::Vector2f velocity, float x, float y) :
CircleShape(4),
velocity(velocity.x, 0),
id(identifier++)
{
    //std::cout << "Creating missile id: " << Id() << "\n";
    setPosition(x + 10, y);
    setFillColor(sf::Color(255, 255, 255, 200));
}

Missile::~Missile()
{
    //std::cout << "Destroying missile id: " << Id() << "\n";
}

void Missile::Update(float elapsedTime)
{
    velocity.x += 1000;
    velocity.x *= elapsedTime;

    move(velocity);
}

unsigned int Missile::Id()
{
    return id;
}