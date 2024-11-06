#include "Bomb.h"
#include <cstdlib>

Bomb::Bomb(int width, int height, const sf::Texture& texture)
    : width(width), height(height), speed(1.0f), direction(1, 0) {
    sprite.setTexture(texture);
    Spawn({});
}
sf::Vector2i Bomb::GetPosition() const {
    return position;
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
    sf::RectangleShape bomb(sf::Vector2f(30, 30));
    bomb.setFillColor(sf::Color::Yellow);
    bomb.setPosition((position.x + 1) * 20, (position.y + 1) * 20);
    window.draw(bomb);
}
void Bomb::Move() {
    position += direction;
    if (position.x < 0 || position.x >= width || position.y < 0 || position.y >= height) {
        direction = -direction;
        position += direction;
    }

    if (changeDirectionTimer.getElapsedTime().asSeconds() >= 3.0f) {
        direction.x = (rand() % 3) - 1;
        direction.y = (rand() % 3) - 1;


        if (direction.x != 0 && direction.y != 0) {
            direction.y = 0;
        }
        changeDirectionTimer.restart();
    }
}
