#pragma once

#include "stdafx.h"
#include "Game.h"
#include "Star.h"

#define FRAMERATE_LIMIT 60
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_BPP 32
#define WINDOW_TITLE "Lost In Space"

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
    delete star;
}

void Game::Initialize()
{
    isInitialized = true;
    mainWindow.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP), WINDOW_TITLE);
    mainWindow.setFramerateLimit(FRAMERATE_LIMIT);
    mainWindow.setMouseCursorVisible(false);

    star = new Star();

    auto windowSize = mainWindow.getSize();
    star->position = Vector2f(windowSize.x / 2, windowSize.y / 2);
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
        
        // Draw some graphical entities
        Draw();

        // End the current frame and display its contents on screen
        mainWindow.display();
    }
}

void Game::Draw()
{
    star->position.x++;

    if (star->position.x > mainWindow.getSize().x)
    {
        star->position.x = 0;
    }
    
    Vertex vertices[] = { *star };
    mainWindow.draw(vertices, 1, Points);
}