#pragma once

#include "Starfield.h"
#include "Spaceship.h"
#include "Missile.h"
#include "Enemy.h"

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
        void UpdateEnemies(float elapsedTime);
        void AddEnemy(std::shared_ptr<Enemy> enemy);
        void RemoveEnemy(unsigned int id);
        void DetectCollisions();
        void DetectSpaceshipCollision();
        void DrawScore();

    private:
        sf::RenderWindow mainWindow;
        sf::Clock clock;
        sf::Clock enemyClock; // clock used for spawning enemies
        bool isInitialized;
        bool isGameOver;
        unsigned int score;
        sf::Text gameOverText;
        sf::Text scoreText;
        sf::Font font;

        // Game objects and collections of objects
        std::unique_ptr<Starfield> starfield;
        std::unique_ptr<Spaceship> spaceship;        
        std::map<unsigned int, std::shared_ptr<Missile>> missiles;
        std::map<unsigned int, std::shared_ptr<Enemy>> enemies;
};
