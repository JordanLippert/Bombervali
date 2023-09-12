#include "src/Game.h"

int main() {
    // Inicializa o jogo (e o que precisar)
    Game::initializeGame();

    // Inicializa o Loop principal (while true)
    Game::run();
    return 0;
}
