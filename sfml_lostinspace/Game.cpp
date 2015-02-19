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

    
    font.loadFromFile("rock.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(36); // in pixels, not points!
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(0, 0);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(36); // in pixels, not points!
    gameOverText.setColor(sf::Color::White);
    
    starfield = std::unique_ptr<Starfield>(new Starfield(NUM_STARS));
    spaceship = std::unique_ptr<Spaceship>(new Spaceship);

    clock.restart();
    enemyClock.restart();
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
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    score = 0;
                    missiles.clear();
                    enemies.clear();
                    spaceship->setPosition(0, WINDOW_HEIGHT / 2);
                    isGameOver = false;
                }
                    break;
            default: 
                break;
            }
        }
        
        if (isGameOver)            
        {
            gameOverText.setString("Game Over - Score: " + std::to_string(score) + " press Escape to restart.");
            gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
            gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            mainWindow.clear(sf::Color::Black);
            mainWindow.draw(gameOverText);
        }
        else
        {
            // Clear the whole window before rendering a new frame
            mainWindow.clear();
            Update();
            Draw();
        }
        
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
    UpdateEnemies(elapsedTime);
    DetectCollisions();
    DetectSpaceshipCollision();
}

void Game::Draw()
{
    DrawScore();
    mainWindow.draw(*spaceship);
    mainWindow.draw(*starfield);

    for (const auto& item : missiles)
    {        
        mainWindow.draw(*item.second);
    }

    for (const auto& item : enemies)
    {
        mainWindow.draw(*item.second);
    }
}

void Game::DrawScore()
{
    scoreText.setString("Score: " + std::to_string(score));
    mainWindow.draw(scoreText);
}

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
    for (auto& it = missiles.cbegin(); it != missiles.cend();)
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

void Game::AddEnemy(std::shared_ptr<Enemy> enemy)
{
    enemies.insert(std::pair<unsigned int, std::shared_ptr<Enemy>>(enemy->Id(), enemy));
}

void Game::RemoveEnemy(unsigned int id)
{
    std::map<unsigned int, std::shared_ptr<Enemy>>::iterator it;
    it = enemies.find(id);
    enemies.erase(it);
}

void Game::UpdateEnemies(float elapsedTime)
{
    if (enemyClock.getElapsedTime().asSeconds() > 0.5)
    {
        enemyClock.restart();
        AddEnemy(std::shared_ptr<Enemy>(new Enemy));
    }

    for (auto& it = enemies.cbegin(); it != enemies.cend();)
    {
        it->second->Update(elapsedTime);
        if (it->second->getPosition().x < 0)
        {
            enemies.erase(it++);
        }
        else
        {
            it++;
        }
    }
}

void Game::DetectCollisions()
{
    // only find one hit (missile and enemy)
    // if hit, remove objects from collections and exit immediately
    for (const auto& kv : missiles)
    {
        auto missileBounds = kv.second->getGlobalBounds();

        for (const auto& kv : enemies)
        {
            auto enemyBounds = kv.second->getGlobalBounds();

            if (missileBounds.intersects(enemyBounds))
            {
                score++;
                missiles.erase(kv.first);
                enemies.erase(kv.first);
                return;
            }
        }
    }
}

void Game::DetectSpaceshipCollision()
{
    // If the spaceship is hit, GAME OVER MAN, GAME OVER!
    for (const auto& kv : enemies)
    {
        auto enemyBounds = kv.second->getGlobalBounds();
        auto spaceshipBounds = spaceship->getGlobalBounds();

        if (spaceshipBounds.intersects(enemyBounds))
        {
            //std::cout << "GAME OVER!\n";
            isGameOver = true;
            return;
        }
    }
}