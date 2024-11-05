#include "Fruit.h"
#include <cstdlib>

Fruit::Fruit(int width, int height) : width(width), height(height) {
    Spawn({});
}

void Fruit::Spawn(const std::vector<sf::Vector2i>& tail) {
    bool occupied;
    do {
        position.x = rand() % width;
        position.y = rand() % height;
        occupied = false;
        for (const auto& segment : tail) {
            if (segment == position) {
                occupied = true;
                break;
            }
        }
    } while (occupied);
}

void Fruit::Draw(sf::RenderWindow& window) const {
    sf::RectangleShape fruit(sf::Vector2f(20, 20));
    fruit.setFillColor(sf::Color::Red);
    fruit.setPosition((position.x + 1) * 20, (position.y + 1) * 20);
    window.draw(fruit);
}

sf::Vector2i Fruit::GetPosition() const {
    return position;
}
