#include "RenderingEngine.h"
#include <iostream>

RenderingEngine::RenderingEngine(sf::RenderWindow& window, const sf::Font& font)
: window(window), font(font) {
    titleText.setFont(font);
    titleText.setString("Snake");
    titleText.setCharacterSize(35);
    titleText.setFillColor(sf::Color::Red);
    titleText.setPosition(150, 315);

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(25);
    startText.setPosition(150, 200);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(25);
    exitText.setPosition(150, 250);
}


void RenderingEngine::ShowMenu(const sf::Sprite& menuBackgroundSprite, int selectedOption, const std::string& playerName) {
    window.clear();
    window.draw(menuBackgroundSprite);

    sf::Text title("Snake Game", font, 50);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition((window.getSize().x - titleBounds.width) / 2, 160);
    window.draw(title);

    sf::Text name("Player: " + playerName, font, 30);
    sf::FloatRect nameBounds = name.getLocalBounds();
    name.setPosition((window.getSize().x - nameBounds.width) / 2, 270);
    window.draw(name);

    std::string startText = (selectedOption == 0) ? "> Start Game <" : "Start Game";
    std::string exitText = (selectedOption == 1) ? "> Exit <" : "Exit";

    sf::Text startOption(startText, font, 30);
    sf::FloatRect startBounds = startOption.getLocalBounds();
    startOption.setPosition((window.getSize().x - startBounds.width) / 2, 360);
    window.draw(startOption);

    sf::Text exitOption(exitText, font, 30);
    sf::FloatRect exitBounds = exitOption.getLocalBounds();
    exitOption.setPosition((window.getSize().x - exitBounds.width) / 2, 410);
    window.draw(exitOption);

    window.display();
}

void RenderingEngine::ShowGameOver(const sf::Sprite& gameOverBackgroundSprite,int score, const std::string& playerName) {
    window.clear();
    window.draw(gameOverBackgroundSprite);

    sf::Text gameOverText("GAME OVER", font, 45);
    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setPosition((window.getSize().x - gameOverBounds.width) / 2, 180);
    window.draw(gameOverText);

    sf::Text scoreText( "Score: " + std::to_string(score), font, 25);
    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setPosition((window.getSize().x - scoreBounds.width) / 2, 350);
    window.draw(scoreText);

    sf::Text retryText("Press Enter to Try Again", font, 25);
    sf::FloatRect retryBounds = retryText.getLocalBounds();
    retryText.setPosition((window.getSize().x - retryBounds.width) / 2, 450);
    window.draw(retryText);

    window.display();
}


void RenderingEngine::Render(const sf::Sprite& backgroundSprite, const Snake& snake, const std::vector<Fruit>& fruits, const std::vector<Bomb>& bombs, int score){
    window.clear();
    window.draw(backgroundSprite);

    for (int i = 0; i < windowWidth / 20; i++) {
        sf::RectangleShape wall(sf::Vector2f(20, 20));
        wall.setFillColor(sf::Color::Black);
        wall.setPosition(i * 20, 0);
        window.draw(wall);
        wall.setPosition(i * 20, windowHeight - 20);
        window.draw(wall);
    }
    for (int i = 0; i < windowHeight / 20; i++) {
        sf::RectangleShape wall(sf::Vector2f(20, 20));
        wall.setFillColor(sf::Color::Black);
        wall.setPosition(0, i * 20);
        window.draw(wall);
        wall.setPosition(windowWidth - 20, i * 20);
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
    scoreText.setCharacterSize(15);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(25, windowHeight - 20);
    window.draw(scoreText);

    window.display();
}
