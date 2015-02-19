#include "stdafx.h"
#include "Enemy.h"
#include "Game.h"

static unsigned int identifier = 0;

Enemy::Enemy() :
RectangleShape(sf::Vector2f(40, 40)),
velocity(0, 0),
id(identifier++)
{
    //std::cout << "Creating enemy id: " << Id() << "\n";
    setPosition(1024, (float)(rand() % 768 ));
    setFillColor(sf::Color(255, 255, 255, rand() % 255 + 50));
}

Enemy::~Enemy()
{
    //std::cout << "Destroying enemy id: " << Id() << "\n";
}

void Enemy::Update(float elapsedTime)
{
    move(-300 * elapsedTime, 0);
    float x = getPosition().x;  
    float y = getPosition().y + sin(x / 100) * (rand() % 10 + 1);
    setPosition(x, y);
    rotate(-1);
}

unsigned int Enemy::Id()
{
    return id;
}
