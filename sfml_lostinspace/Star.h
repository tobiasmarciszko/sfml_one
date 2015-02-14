#pragma once

enum StarType {
    Slow = 0, 
    Medium, 
    Fast,
};

class Star : public sf::Vertex
{
public:
    Star();
    ~Star();

    void Update();

private: 
    StarType starType;
};
