#include "GameEngine.h"


GameEngine::GameEngine(const std::string& playerName)
    : window(sf::VideoMode(1000, 645), "Snake"),
      snake(50, 32),
      isPaused(false),
      score(0) {

    if (!font.loadFromFile("/Users/victorialoziak/Downloads/Arial/ARIAL.TTF")) {
        std::cout << "Could not load font!" << std::endl;
        exit(-1);
    }
    for (int i = 0; i < 5; ++i) {
        Fruit newFruit(50, 32);
        newFruit.Spawn(snake.GetTail());
        fruits.push_back(newFruit);
    }

    for (int i = 0; i < 3; ++i) {
        Bomb newBomb(50, 32);
        newBomb.Spawn(snake.GetTail());
        bombs.push_back(newBomb);
    }
    Setup();
}

void GameEngine::Setup() {
    snake.Setup();
    for (auto& fruit : fruits) {
        fruit.Spawn(snake.GetTail());
    }
    for (auto& bomb : bombs) {
        bomb.Spawn(snake.GetTail());
    }
}

void GameEngine::Run() {
    RenderingEngine renderingEngine(window, font);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            HandleInput(event);
        }

        if (!isPaused && !snake.IsGameOver()) {
            Update();
            renderingEngine.Render(snake, fruits, bombs, score);
            sf::sleep(sf::milliseconds(100));
        }
    }
}


void GameEngine::HandleInput(sf::Event& event) {
    snake.HandleInput(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
            isPaused = !isPaused;
        }
    }
}

void GameEngine::Update() {
    snake.Move();
    for (auto& fruit : fruits) {
        if (snake.Eat(fruit.GetPosition())) {
            score += 10;
            fruit.Spawn(snake.GetTail());
        }
    }
    for (auto& bomb : bombs) {
        if (snake.Trigger(bomb.GetPosition())) {
            score -=10;
            bomb.Spawn(snake.GetTail());
            if (snake.GetTailLength() == 0) {
                snake.gameOver = true;
            }

        }
    }
}

bool GameEngine::IsGameOver() const {
    return snake.IsGameOver();
}
