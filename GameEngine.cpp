#include "GameEngine.h"


GameEngine::GameEngine()
    : window(sf::VideoMode(736, 736), "Snake"),
      state(GameState::MENU),
      snake(50, 32),
      isPaused(false),
      gameOver(false),
      selectedOption(0),
      score(0) {

    if (!font.loadFromFile("/Users/victorialoziak/Downloads/Press_Start_2P/PressStart2P-Regular.ttf")) {
        std::cout << "Could not load font!" << std::endl;
        exit(-1);
    }

    if (!menuBackgroundTexture.loadFromFile("/Users/victorialoziak/Downloads/img2.jpeg")) {
        std::cout << "Could not load menu background image!" << std::endl;
        exit(-1);
    }
    if (!gameBackgroundTexture.loadFromFile("/Users/victorialoziak/Downloads/6.jpeg")) {
        std::cout << "Could not load game background image!" << std::endl;
        exit(-1);
    }
    if (!gameOverBackgroundTexture.loadFromFile("/Users/victorialoziak/Downloads/img2.jpeg")) {
        std::cout << "Could not load game over background image!" << std::endl;
        exit(-1);
    }

    if (!fruitTexture.loadFromFile("/Users/victorialoziak/Downloads/img10.png")) {
        std::cerr << "Could not load fruit image!" << std::endl;
        exit(-1);
    }
    if (!bombTexture.loadFromFile("/Users/victorialoziak/Downloads/img11.png")) {
        std::cerr << "Could not load bomb image!" << std::endl;
        exit(-1);
    }

    menuBackgroundSprite.setTexture(menuBackgroundTexture);
    gameBackgroundSprite.setTexture(gameBackgroundTexture);
    gameOverBackgroundSprite.setTexture(gameOverBackgroundTexture);
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
                renderer.Render(gameBackgroundSprite, snake, fruits, bombs, score);
                sf::sleep(sf::milliseconds(100));
            break;
            case GameState::MENU:
                renderer.ShowMenu(menuBackgroundSprite, selectedOption, playerName);

            break;
            case GameState::GAME_OVER:
                renderer.ShowGameOver(gameOverBackgroundSprite, score, playerName, selectedOption);
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
        if (event.key.code == sf::Keyboard::Left) {
            selectedOption = (selectedOption - 1 + 2) % 2;
        } else if (event.key.code == sf::Keyboard::Right) {
            selectedOption = (selectedOption + 1) % 2;
        } else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedOption == 0) {
                ResetGame();
                state = GameState::PLAYING;
                StartGame();
            } else if (selectedOption == 1) {
                ResetGame();
                playerName.clear();
                state = GameState::MENU;
            }
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

    for (int i = 0; i < 15; ++i) {
        Fruit newFruit(46, 30, fruitTexture);
        newFruit.Spawn(snake.GetTail());
        fruits.push_back(newFruit);
    }

    for (int i = 0; i < 5; ++i) {
        Bomb newBomb(46, 30, bombTexture);
        newBomb.Spawn(snake.GetTail());
        bombs.push_back(newBomb);
    }

    Setup();
}

void GameEngine::ResetGame() {
    fruits.clear();
    bombs.clear();
    score = 0;
}

bool GameEngine::IsGameOver() const {
    return gameOver;
}
