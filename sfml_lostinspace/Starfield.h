#pragma once

#include "Star.h"

typedef std::vector<Star*> Stars;

class Starfield : public sf::Drawable, public sf::Transformable
{
public:
    Starfield();
    ~Starfield();

public:
    Stars GetStars();
    void Update();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const auto& star : stars)
        {
            target.draw((sf::Vertex*)star, 1, sf::Points);
        }
    }

private:
    Stars stars;
};

