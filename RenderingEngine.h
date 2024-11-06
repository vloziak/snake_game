#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include <string>
#include "Snake.h"
#include "Fruit.h"

class RenderingEngine {
public:
    RenderingEngine(sf::RenderWindow& window, const sf::Font& font);
    void Render(const sf::Sprite& backgroundSprite, const Snake& snake, const std::vector<Fruit>& fruits, const std::vector<Bomb>& bombs, int score);
    sf::FloatRect getStartTextBounds() const;
    sf::FloatRect getExitTextBounds() const;
    void ShowMenu(const sf::Sprite& menuBackgroundSprite, int selectedOption, const std::string& playerName);
    void ShowGameOver(const sf::Sprite& gameOverBackgroundSprite, int score, const std::string& playerName, int selectedOption);

private:
    sf::RenderWindow& window;
    const int windowWidth = 736;
    const int windowHeight = 736;
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text exitText;
};

#endif // RENDERINGENGINE_H
