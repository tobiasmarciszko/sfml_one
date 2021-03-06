#include "stdafx.h"
#include "Starfield.h"
#include "Star.h"

Starfield::Starfield(unsigned int count) : 
stars(count),
vertices(sf::Points, count)
{
}

Starfield::~Starfield()
{
}

void Starfield::Update()
{
    for (size_t i = 0; i < stars.size(); ++i)
    {
        stars[i].Update();
        vertices[i].color = stars[i].color;
        vertices[i].position = stars[i].position;
    }
}

void Starfield::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //states.transform *= getTransform();
    //states.texture = NULL;
    target.draw(vertices, states);
}
