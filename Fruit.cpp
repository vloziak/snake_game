#include "Fruit.h"
#include <cstdlib>

Fruit::Fruit(int width, int height, const sf::Texture& texture) : width(width), height(height) {
    sprite.setTexture(texture);
    sprite.setScale(0.2f, 0.2f);
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


void Fruit::Draw(sf::RenderWindow& window) const{
    sf::RectangleShape bomb(sf::Vector2f(25, 25));
    bomb.setFillColor(sf::Color::Magenta);
    bomb.setPosition((position.x + 1) * 20, (position.y + 1) * 20);
    window.draw(bomb);
}

sf::Vector2i Fruit::GetPosition() const {
    return position;
}
