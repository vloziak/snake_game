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

private:
    sf::RenderWindow& window;
    sf::Font font;
};

#endif // RENDERINGENGINE_H
