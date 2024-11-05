#include "RenderingEngine.h"
#include <iostream>

RenderingEngine::RenderingEngine(sf::RenderWindow& window, const sf::Font& font)
: window(window), font(font) {
    titleText.setFont(font);
    titleText.setString("Snake");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Red);
    titleText.setPosition(500, 315);

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(30);
    startText.setPosition(200, 200);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(30);
    exitText.setPosition(200, 250);
}

void RenderingEngine::ShowMenu(int selectedOption, const std::string& playerName) {
    window.clear();

    sf::Text title("Snake Game", font, 50);
    title.setPosition(400, 50);
    window.draw(title);

    sf::Text name("Player: " + playerName, font, 30);
    name.setPosition(400, 150);
    window.draw(name);

    std::string startText = (selectedOption == 0) ? "> Start Game <" : "Start Game";
    std::string exitText = (selectedOption == 1) ? "> Exit <" : "Exit";

    sf::Text startOption(startText, font, 30);
    startOption.setPosition(400, 250);
    window.draw(startOption);

    sf::Text exitOption(exitText, font, 30);
    exitOption.setPosition(400, 300);
    window.draw(exitOption);

    window.display();
}

void RenderingEngine::ShowGameOver(int score, const std::string& playerName) {
    window.clear();

    sf::Text gameOverText("GAME OVER", font, 50);
    gameOverText.setPosition(400, 50);
    window.draw(gameOverText);

    sf::Text scoreText("Score: " + std::to_string(score), font, 30);
    scoreText.setPosition(400, 150);
    window.draw(scoreText);

    sf::Text retryText("Press Enter to Try Again", font, 30);
    retryText.setPosition(400, 250);
    window.draw(retryText);

    window.display();
}


void RenderingEngine::Render(const Snake& snake, const std::vector<Fruit>& fruits, const std::vector<Bomb>& bombs, int score){
    window.clear();
    for (int i = 0; i < 50; i++) {
        sf::RectangleShape wall(sf::Vector2f(20, 20));
        wall.setFillColor(sf::Color::Red);
        wall.setPosition(i * 20, 0);
        window.draw(wall);
        wall.setPosition(i * 20, 645);
        window.draw(wall);
    }
    for (int i = 0; i < 32; i++) {
        sf::RectangleShape wall(sf::Vector2f(20, 20));
        wall.setFillColor(sf::Color::Red);
        wall.setPosition(0, i * 20);
        window.draw(wall);
        wall.setPosition(980, i * 20);
        window.draw(wall);
    }
     snake.Draw(window);

    for (const auto& fruit : fruits) {
        fruit.Draw(window);
    }
    for (const auto& bomb : bombs) {
        bomb.Draw(window);
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(25, 625);
    window.draw(scoreText);

    window.display();
}
