//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_GAMESTATISTICS_H
#define GAME02_CBP_GAMESTATISTICS_H


#include <cstdlib>
#include <ctime>

namespace GameStatistics {
    // Variáveis para medir o tempo de jogo
    clock_t end, start;
    int duration;
    bool startedTimer = false;

    // Variáveis para armazenar as estatísticas do jogo
    int gameTime = 0;
    int amountOfBombsPlaced = 0;

    // Função chamada a cada ciclo do jogo
    void tick() {
        // Resetar o início do relógio caso necessário
        if (duration == 0 && !startedTimer) {
            start = clock();
            startedTimer = true;
        }

        end = clock();

        // Calcular a duração do ciclo em segundos
        duration = (end - start) / CLOCKS_PER_SEC;

        if (duration >= 1) {
            duration = 0;

            // Variável para controlar se o contador deve reiniciar
            startedTimer = false;

            // Incrementar o tempo de jogo a cada segundo
            gameTime++;
        }
    }
}

#endif //GAME02_CBP_GAMESTATISTICS_H
