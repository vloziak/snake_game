#include "Bomb.h"
#include <cstdlib>

Bomb::Bomb(int width, int height) : width(width), height(height) {
    Spawn({});
}

void Bomb::Spawn(const std::vector<sf::Vector2i>& tail) {
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

void Bomb::Draw(sf::RenderWindow& window) const {
    sf::RectangleShape bomb(sf::Vector2f(20, 20));
    bomb.setFillColor(sf::Color::Green);
    bomb.setPosition((position.x + 1) * 20, (position.y + 1) * 20);
    window.draw(bomb);
}

sf::Vector2i Bomb::GetPosition() const {
    return position;
}
