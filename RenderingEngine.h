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
    void Render(const Snake& snake, const std::vector<Fruit>& fruits, const std::vector<Bomb>& bombs, int score);
    sf::FloatRect getStartTextBounds() const;
    sf::FloatRect getExitTextBounds() const;
    void ShowMenu(int selectedOption, const std::string& playerName);
    void ShowGameOver(int score, const std::string& playerName);

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text exitText;
};

#endif // RENDERINGENGINE_H
