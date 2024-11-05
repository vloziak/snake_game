#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Snake {
public:
    Snake(int width, int height);
    void Setup();
    void Move();
    void HandleInput(sf::Event& event);
    void Draw(sf::RenderWindow& window) const;
    bool HasSelfCollision() const;
    bool Eat(const sf::Vector2i& fruitPos);
    bool Trigger(const sf::Vector2i& bombPos);
    std::vector<sf::Vector2i> GetTail() const;
    int GetTailLength() const;

private:
    int width, height;
    int x, y, nTail;
    std::vector<sf::Vector2i> tail;
    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    Direction dir;
};

#endif // SNAKE_H
