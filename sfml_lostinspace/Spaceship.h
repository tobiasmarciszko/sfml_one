#pragma once

class Spaceship : public sf::Sprite
{
public:
    Spaceship();
    ~Spaceship();

    void Update(float elapsedTime);

private:
    sf::Texture texture;
    sf::Vector2f velocity;
};
