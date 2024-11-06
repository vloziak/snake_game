#include "Snake.h"
#include <cstdlib>
#include <ctime>

Snake::Snake(int width, int height)
    : width(width), height(height), nTail(0), dir(STOP) {
    srand(static_cast<unsigned>(time(0)));
}

void Snake::Setup() {
    dir = STOP;
    x = width / 2;
    y = height / 2;
    nTail = 0;
    tail.clear();
}

void Snake::Move() {
    if (nTail > 0) {
        tail.insert(tail.begin(), {x, y});
        if (tail.size() > nTail) {
            tail.pop_back();
        }
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
}

bool Snake::HasSelfCollision() const {
    for (const auto& segment : tail) {
        if (segment.x == x && segment.y == y) {
            return true;
        }
    }
    return false;
}

void Snake::HandleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::A: dir = LEFT; break;
            case sf::Keyboard::D: dir = RIGHT; break;
            case sf::Keyboard::W: dir = UP; break;
            case sf::Keyboard::S: dir = DOWN; break;
            default: break;
        }
    }
}

void Snake::Draw(sf::RenderWindow& window) const{
    sf::RectangleShape snakeHead(sf::Vector2f(30, 30));
    snakeHead.setFillColor(sf::Color::Red);
    snakeHead.setPosition((x + 1) * 20, (y + 1) * 20);
    window.draw(snakeHead);

    for (const auto& segment : tail) {
        sf::RectangleShape tailSegment(sf::Vector2f(30, 30));
        tailSegment.setFillColor(sf::Color::Black);
        tailSegment.setPosition((segment.x + 1) * 20, (segment.y + 1) * 20);
        window.draw(tailSegment);
    }
}

bool Snake::Eat(const sf::Vector2i& fruitPos) {
    if (x == fruitPos.x && y == fruitPos.y) {
        nTail++;
        return true;
    }
    return false;
}


bool Snake::Trigger(const sf::Vector2i& bombPos) {
    if (x == bombPos.x && y == bombPos.y) {
        if (!tail.empty()) {
            tail.pop_back();
            nTail = std::max(0, nTail - 1);
        }
        return true;
    }
    return false;
}

std::vector<sf::Vector2i> Snake::GetTail() const {
    return tail;
}

int Snake::GetTailLength() const {
    return nTail;
}