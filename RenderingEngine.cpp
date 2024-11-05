#include "RenderingEngine.h"
#include <iostream>

RenderingEngine::RenderingEngine(sf::RenderWindow& window, const sf::Font& font)
    : window(window), font(font) {}

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
