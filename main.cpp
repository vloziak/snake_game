#include <iostream>
#include "GameEngine.h"

int main() {
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;

    GameEngine game(playerName);
    game.Run();

    return 0;
}
