#pragma once

class Star;

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
        void Draw();
        void Cleanup();

    private:
        sf::RenderWindow mainWindow;
        bool isInitialized;
        Star* star;
};
