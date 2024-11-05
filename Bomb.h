#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <vector>

class Bomb {
public:
    Bomb(int width, int height);
    void Spawn(const std::vector<sf::Vector2i>& tail);
    void Draw(sf::RenderWindow& window) const;
    sf::Vector2i GetPosition() const;

private:
    int width, height;
    sf::Vector2i position;
};

#endif // BOMB_H
