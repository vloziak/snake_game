#include "Snake.h"
#include <cstdlib>
#include <ctime>

Snake::Snake(int width, int height)
    : width(width), height(height), gameOver(false), nTail(0), dir(STOP) {
    srand(static_cast<unsigned>(time(0)));
}

void Snake::Setup() {
    gameOver = false;
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

    for (const auto& segment : tail) {
        if (segment.x == x && segment.y == y) {
            gameOver = true;
        }
    }
}

void Snake::HandleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::A: dir = LEFT; break;
            case sf::Keyboard::D: dir = RIGHT; break;
            case sf::Keyboard::W: dir = UP; break;
            case sf::Keyboard::S: dir = DOWN; break;
            case sf::Keyboard::Escape: gameOver = true; break;
            default: break;
        }
    }
}

void Snake::Draw(sf::RenderWindow& window) const{
    sf::RectangleShape snakeHead(sf::Vector2f(20, 20));
    snakeHead.setFillColor(sf::Color::Blue);
    snakeHead.setPosition((x + 1) * 20, (y + 1) * 20);
    window.draw(snakeHead);

    for (const auto& segment : tail) {
        sf::RectangleShape tailSegment(sf::Vector2f(20, 20));
        tailSegment.setFillColor(sf::Color::White);
        tailSegment.setPosition((segment.x + 1) * 20, (segment.y + 1) * 20);
        window.draw(tailSegment);
    }
}

bool Snake::IsGameOver() const {
    return gameOver;
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
        tail.pop_back();
        nTail--;
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