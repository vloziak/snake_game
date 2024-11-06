#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include <vector>

class Fruit {
public:
    Fruit(int width, int height,const sf::Texture& texture);
    void Spawn(const std::vector<sf::Vector2i>& tail);
    void SetPosition(float x, float y);
    void Draw(sf::RenderWindow& window)const;
    sf::Vector2i GetPosition() const;

private:
    int width, height;
    sf::Vector2i position;
    sf::Sprite sprite;
};

#endif // FRUIT_H
