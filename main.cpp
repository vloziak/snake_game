#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 17;
int x, y, fruitX, fruitY, score;
vector<pair<int, int>> tail;
int nTail;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
bool isPaused = false;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    tail.clear();
}

void RenderingEngine(sf::RenderWindow &window, sf::Font &font, const string &playerName) {
    window.clear();

    for (int i = 0; i < width + 2; i++) {
        sf::RectangleShape wall(sf::Vector2f(20, 20));
        wall.setFillColor(sf::Color::Red);
        wall.setPosition(i * 20, 0);
        window.draw(wall);
        wall.setPosition(i * 20, (height + 1) * 20);
        window.draw(wall);
    }
    for (int i = 0; i < height + 2; i++) {
        sf::RectangleShape wall(sf::Vector2f(20, 20));
        wall.setFillColor(sf::Color::Red);
        wall.setPosition(0, i * 20);
        window.draw(wall);
        wall.setPosition((width + 1) * 20, i * 20);
        window.draw(wall);
    }

    sf::RectangleShape snakeHead(sf::Vector2f(20, 20));
    snakeHead.setFillColor(sf::Color::Green);
    snakeHead.setPosition((x + 1) * 20, (y + 1) * 20);
    window.draw(snakeHead);

    for (auto segment : tail) {
        sf::RectangleShape tailSegment(sf::Vector2f(20, 20));
        tailSegment.setFillColor(sf::Color::Yellow);
        tailSegment.setPosition((segment.first + 1) * 20, (segment.second + 1) * 20);
        window.draw(tailSegment);
    }

    sf::RectangleShape fruit(sf::Vector2f(20, 20));
    fruit.setFillColor(sf::Color::Magenta);
    fruit.setPosition((fruitX + 1) * 20, (fruitY + 1) * 20);
    window.draw(fruit);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(playerName + "'s Score: " + to_string(score));
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, (height + 2) * 20);
    window.draw(scoreText);

    window.display();
}

void GameEngine() {
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

    for (auto segment : tail) {
        if (segment.first == x && segment.second == y) {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void HandleInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::A: dir = LEFT; break;
            case sf::Keyboard::D: dir = RIGHT; break;
            case sf::Keyboard::W: dir = UP; break;
            case sf::Keyboard::S: dir = DOWN; break;
            case sf::Keyboard::P: isPaused = !isPaused; break;
            case sf::Keyboard::Escape: gameOver = true; break;
            default: break;
        }
    }
}

int main() {
    srand(time(0));

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    sf::RenderWindow window(sf::VideoMode((width + 2) * 20, (height + 3) * 20), "Snake Game with SFML");
    sf::Font font;
    if (!font.loadFromFile("/Users/victorialoziak/Downloads/Arial/ARIAL.TTF")) {
        cout << "Could not load font!" << endl;
        return -1;
    }

    Setup();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            HandleInput(event);
        }

        if (!isPaused && !gameOver) {
            GameEngine();
            RenderingEngine(window, font, playerName);
            sf::sleep(sf::milliseconds(100));
        }
    }

    cout << "Game Over! Your score: " << score << endl;
    return 0;
}
