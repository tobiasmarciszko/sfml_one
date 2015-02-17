#pragma once

class Missile : public sf::CircleShape
{
public:
    Missile(sf::Vector2f velocity, float x, float y);
    ~Missile();

    void Update(float elapsedTime);
    unsigned int Id();

private:
    sf::Vector2f velocity;
    unsigned int id;
};
