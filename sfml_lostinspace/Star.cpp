#include "stdafx.h"
#include "Star.h"

using namespace sf;

Star::Star()
{
    position.x = (float)(rand() % 1024 + 1);
    position.y = (float)(rand() % 768  + 1);

    Color colors[] = { Color(255, 255, 255, 100), Color(255, 255, 255, 200), Color(255, 255, 255, 255), };
    int index = rand() % 3;
    color = colors[index];
    starType = (StarType)index;
}

Star::~Star()
{
}

void Star::Update()
{
    int speed;
    switch (starType)
    {
        case StarType::Slow:
            speed = 1;
            break;
        case StarType::Medium :
            speed = 2;
            break;
        case StarType::Fast :
            speed = 4;
            break;
        default: 
            break;
    }

    position.x -= speed;

    if (position.x < 0)
    {
        position.x = 1024;
    }
}