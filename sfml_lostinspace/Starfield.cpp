#include "stdafx.h"
#include "Starfield.h"
#include "Star.h"

#define NUM_STARS 250

using namespace sf;

Starfield::Starfield()
{
    for (int i = 0; i < NUM_STARS; ++i)
    {
        stars.push_back(new Star);
    }
}

Starfield::~Starfield()
{
}

Stars Starfield::GetStars()
{
    return stars;
}

void Starfield::Update()
{
    for (int i = 0; i < NUM_STARS; ++i)
    {
        stars[i]->Update();
    }
}