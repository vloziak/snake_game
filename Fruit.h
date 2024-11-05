#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include <vector>

class Fruit {
public:
    Fruit(int width, int height);
    void Spawn(const std::vector<sf::Vector2i>& tail);
    void Draw(sf::RenderWindow& window) const;
    sf::Vector2i GetPosition() const;

private:
    int width, height;
    sf::Vector2i position;
};

#endif // FRUIT_H
