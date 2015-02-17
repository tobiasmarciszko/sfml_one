#pragma once

#include "Starfield.h"
#include "Spaceship.h"
#include "Missile.h"

// The main class for handling game states and event loop updates
class Game
{
    public:
        static Game& get(){
            static Game instance;
            return instance;
        }

        void Run();
        void AddMissile(std::shared_ptr<Missile> missile);
        void RemoveMissile(unsigned int id);

    private:
        void Initialize();
        void EventLoop();
        void Update();
        void Draw();
        void Cleanup();
        void UpdateMissiles(float elapsedTime);

    private:
        sf::RenderWindow mainWindow;
        sf::Clock clock;
        bool isInitialized;

        // Game objects
        std::unique_ptr<Starfield> starfield;
        std::unique_ptr<Spaceship> spaceship;        
        std::map<unsigned int, std::shared_ptr<Missile>> missiles;
};
