#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Fruit.h"
#include "Bomb.h"
#include "RenderingEngine.h"
#include <vector>
#include <iostream>


class GameEngine {
public:
    GameEngine(const std::string& playerName);
    void Run();
    void Setup();
    void HandleInput(sf::Event& event);
    void Update();
    bool IsGameOver() const;

private:
    sf::RenderWindow window;
    sf::Font font;
    Snake snake;
    std::vector<Fruit> fruits;
    std::vector<Bomb> bombs;
    bool isPaused;
    int score;
};

#endif // GAMEENGINE_H
