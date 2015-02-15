#pragma once

#include "Starfield.h"
#include "Spaceship.h"

// The main class for handling game states and event loop updates
class Game
{
    public:
        static Game& get(){
            static Game instance;
            return instance;
        }

        void Run();

    private:
        void Initialize();
        void EventLoop();
        void Update();
        void Draw();
        void Cleanup();

    private:
        sf::RenderWindow mainWindow;
        bool isInitialized;
        std::unique_ptr<Starfield> starfield;
        std::unique_ptr<Spaceship> spaceship;
        sf::Clock clock;
};
