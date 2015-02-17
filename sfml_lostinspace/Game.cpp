#pragma once

#include "stdafx.h"
#include "Game.h"

#define FRAMERATE_LIMIT 60
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_BPP 32
#define AA_LEVEL 0
#define WINDOW_TITLE "Lost In Space"
#define NUM_STARS 300

void Game::Run()
{
    if (!isInitialized)
    {
        Initialize();
    }

    EventLoop();
    Cleanup();
}

void Game::Cleanup()
{    
}

void Game::Initialize()
{
    isInitialized = true;
    sf::ContextSettings settings;
    settings.antialiasingLevel = AA_LEVEL;
    mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP), WINDOW_TITLE, sf::Style::Default, settings);
    mainWindow.setFramerateLimit(FRAMERATE_LIMIT);
    mainWindow.setMouseCursorVisible(false);

    starfield = std::unique_ptr<Starfield>(new Starfield(NUM_STARS));
    spaceship = std::unique_ptr<Spaceship>(new Spaceship);
}

void Game::EventLoop()
{
    while (mainWindow.isOpen())
    {
        // Event processing
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                mainWindow.close();
                break;
            default: 
                break;
            }
        }
        
        // Clear the whole window before rendering a new frame
        mainWindow.clear();
        
        Update();
        Draw();

        // End the current frame and display its contents on screen
        mainWindow.display();
    }
}

void Game::Update()
{
    float elapsedTime = clock.restart().asSeconds();
    spaceship->Update(elapsedTime);
    starfield->Update();
    UpdateMissiles(elapsedTime);
}

void Game::Draw()
{
    mainWindow.draw(*spaceship);
    mainWindow.draw(*starfield);

    for each (const auto& item in missiles)
    {        
        mainWindow.draw(*item.second);
    }
}

// Lightweight object management
void Game::AddMissile(std::shared_ptr<Missile> missile)
{
    missiles.insert(std::pair<unsigned int, std::shared_ptr<Missile>>(missile->Id(), missile));
}

void Game::RemoveMissile(unsigned int id)
{
    std::map<unsigned int, std::shared_ptr<Missile>>::iterator it;
    it = missiles.find(id);
    missiles.erase(it);
}

void Game::UpdateMissiles(float elapsedTime)
{
    for (auto it = missiles.cbegin(); it != missiles.cend();)
    {
        it->second->Update(elapsedTime);
        if (it->second->getPosition().x > WINDOW_WIDTH)
        {
            missiles.erase(it++);
        }
        else
        {
            it++;
        }
    }
}
