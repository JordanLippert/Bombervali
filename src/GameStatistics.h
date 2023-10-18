//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_GAMESTATISTICS_H
#define GAME02_CBP_GAMESTATISTICS_H


#include <cstdlib>
#include <ctime>

namespace GameStatistics {
    clock_t end, start;
    int duration;
    bool startedTimer = false;

    int gameTime = 0;
    int amountOfBombsPlaced = 0;
    int fps = 0;
    int coutingFps = 0;

    void tick() {
        coutingFps++;
        // Resetar o ínicio do clock caso necessário
        if (duration == 0 && !startedTimer) {
            start = clock();
            startedTimer = true;
        }

        end = clock();
        // Calcular duração do ciclo
        duration = (end - start) / CLOCKS_PER_SEC;

        if (duration >= 1) {
            duration = 0;
            fps = coutingFps;
            coutingFps = 0;
            // Variável para controlar se o contador deve reiniciar
            startedTimer = false;

            gameTime++;
        }
    }
}

#endif //GAME02_CBP_GAMESTATISTICS_H
