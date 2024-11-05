#include "GameEngine.h"


GameEngine::GameEngine()
    : window(sf::VideoMode(1000, 645), "Snake"),
      state(GameState::MENU),
      snake(50, 32),
      isPaused(false),
      gameOver(false),
      selectedOption(0),
      score(0) {

    if (!font.loadFromFile("/Users/victorialoziak/Downloads/Arial/ARIAL.TTF")) {
        std::cout << "Could not load font!" << std::endl;
        exit(-1);
    }
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
    RenderingEngine renderer(window, font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            switch (state) {
                case GameState::MENU:
                    HandleMenuInput(event);
                break;
                case GameState::PLAYING:
                    HandlePlayingInput(event);
                break;
                case GameState::GAME_OVER:
                    HandleGameOverInput(event);
                break;
            }
        }
        switch (state) {
            case GameState::PLAYING:
                Update();
                renderer.Render(snake, fruits, bombs, score);
                sf::sleep(sf::milliseconds(100));
            break;
            case GameState::MENU:
                renderer.ShowMenu(selectedOption, playerName);
            break;
            case GameState::GAME_OVER:
                renderer.ShowGameOver(score, playerName);
            break;
        }
    }
}


void GameEngine::HandleMenuInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == '\b' && !playerName.empty()) {
                playerName.pop_back();
            } else {
                playerName += static_cast<char>(event.text.unicode);
            }
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedOption = (selectedOption - 1 + 2) % 2;
        } else if (event.key.code == sf::Keyboard::Down) {
            selectedOption = (selectedOption + 1) % 2;
        } else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedOption == 0) {
                StartGame();
                state = GameState::PLAYING;
            } else if (selectedOption == 1) {
                window.close();
            }
        }
    }
}

void GameEngine::HandlePlayingInput(sf::Event& event) {
    snake.HandleInput(event);
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
            isPaused = !isPaused;
        }
    }
}

void GameEngine::HandleGameOverInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            ResetGame();
        }
    }
}

void GameEngine::Update() {
    snake.Move();

    if (snake.HasSelfCollision()) {
        state = GameState::GAME_OVER;
    }

    for (auto& fruit : fruits) {
        if (snake.Eat(fruit.GetPosition())) {
            score += 10;
            fruit.Spawn(snake.GetTail());
        }
    }

    for (auto& bomb : bombs) {
        bomb.Move();
        if (snake.Trigger(bomb.GetPosition())) {
            if(score != 0){score -=10;}
            bomb.Spawn(snake.GetTail());
            if (snake.GetTailLength() == 0) {
                state = GameState::GAME_OVER;
            }
        }
    }
}

void GameEngine::StartGame() {
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

void GameEngine::ResetGame() {
    fruits.clear();
    bombs.clear();
    score = 0;
    playerName.clear();
    state = GameState::MENU; //
}

bool GameEngine::IsGameOver() const {
    return gameOver;
}
