//
// Created by caior on 29/08/2023.
//

#ifndef GAME02_ENEMIES_H
#define GAME02_ENEMIES_H

#include <ctime>
#include "Player.h"

struct Enemy {
    int row;
    int column;
    bool isLive;
};

namespace Enemies {
    clock_t end, start;
    int duration;
    bool startedTimer = false;

    Enemy enemies[3];

    // Está função deve retornar se todos os inimigos estão mortos
    bool areAllEnemiesDead() {
        return false;
    }

    // Função para mover os inimigos de forma randômica
    void moveEnemies() {

    }

    // Função para colocar as bombas dos inimigos
    void placeBombs() {

    }

    void tick() {
        // Resetar o ínicio do clock caso necessário
        if (duration == 0 && !startedTimer) {
            start = clock();
            startedTimer = true;
        }

        end = clock();
        // Calcular duração do ciclo
        duration = (end - start) / CLOCKS_PER_SEC;

        if (duration == 1) {
            duration = 0;
            // Variavel para controlar se o contador deve reiniciar
            startedTimer = false;

            // Mover e colocar as bombas dos inimigos
            moveEnemies();
            placeBombs();
        }
    }

    void initEnemies() {

    }
}

#endif //GAME02_ENEMIES_H
