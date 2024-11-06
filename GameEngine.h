#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Fruit.h"
#include "Bomb.h"
#include "RenderingEngine.h"
#include <vector>
#include <iostream>

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

class GameEngine {
public:
    GameEngine();
    void Run();


private:
    void HandleMenuInput(sf::Event& event);
    void HandlePlayingInput(sf::Event& event);
    void HandleGameOverInput(sf::Event& event);

    void Update();
    void ShowMenu(int selectedOption, const std::string& playerName);
    void ShowGameOver(int score, const std::string& playerName);
    void StartGame();
    void ResetGame();
    bool IsGameOver() const;
    void Setup();


    GameState state;
    sf::RenderWindow window;
    sf::Font font;
    Snake snake;
    std::vector<Fruit> fruits;
    std::vector<Bomb> bombs;
    bool gameOver;
    bool isPaused;
    int score;
    std::string playerName;
    int selectedOption;

    sf::Texture fruitTexture;
    sf::Texture bombTexture;

    sf::Texture menuBackgroundTexture;
    sf::Texture gameBackgroundTexture;
    sf::Texture gameOverBackgroundTexture;

    sf::Sprite menuBackgroundSprite;
    sf::Sprite gameBackgroundSprite;
    sf::Sprite gameOverBackgroundSprite;
};

#endif // GAMEENGINE_H
