#pragma once

class Enemy : public sf::RectangleShape
{
public:
    Enemy();
    ~Enemy();

    void Update(float elapsedTime);
    unsigned int Id();

private:
    sf::Vector2f velocity;
    unsigned int id;
};
