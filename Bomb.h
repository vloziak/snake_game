#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <vector>

class Bomb {
public:
    Bomb(int width, int height, const sf::Texture& texture);
    void Spawn(const std::vector<sf::Vector2i>& tail);
    void Draw(sf::RenderWindow& window) const;
    void Move();
    sf::Vector2i GetPosition() const;


private:
    int width, height;
    sf::Vector2i position;
    sf::Vector2i direction;
    float speed;
    sf::Clock changeDirectionTimer;
    sf::Sprite sprite;
};

#endif // BOMB_H
