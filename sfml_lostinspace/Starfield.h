#pragma once

#include "Star.h"

class Starfield : 
    public sf::Drawable, 
    public sf::Transformable
{
public:
    Starfield(unsigned int count);
    ~Starfield();

public:
    void Update();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::vector<Star> stars;
    sf::VertexArray vertices;
};
