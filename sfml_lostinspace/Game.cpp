#pragma once

#include "stdafx.h"
#include "Game.h"

#define FRAMERATE_LIMIT 60
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_BPP 32
#define WINDOW_TITLE "Lost In Space"
#define NUM_STARS 250

using namespace sf;
using namespace std;

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
    mainWindow.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP), WINDOW_TITLE);
    mainWindow.setFramerateLimit(FRAMERATE_LIMIT);
    mainWindow.setMouseCursorVisible(false);

    starfield = unique_ptr<Starfield>(new Starfield(NUM_STARS));   
}

void Game::EventLoop()
{
    while (mainWindow.isOpen())
    {
        // Event processing
        Event event;
        while (mainWindow.pollEvent(event))
        {
            // Request for closing the window
            if (event.type == Event::Closed)
                mainWindow.close();
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
    starfield->Update();
}

void Game::Draw()
{     
    mainWindow.draw(*starfield);
}
