#pragma once

#include "Missile.h"

class Spaceship : public sf::Sprite
{
public:
    Spaceship();
    ~Spaceship();

    void Update(float elapsedTime);
    std::shared_ptr<Missile> missile;

private:
    void FireMissile();

private:
    sf::Texture texture;
    sf::Vector2f velocity;
    sf::Clock clock;
};
