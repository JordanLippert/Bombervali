//
// Created by Caio on 25/08/2023.
//

#ifndef GAME02_BOMBS_H
#define GAME02_BOMBS_H

#include "../config.h"
#include "utils/ConsoleColors.h"
#include "enums/GameChar.h"
#include <time.h>

struct Bomb {
    int row;
    int column;
    bool placed;
    clock_t placedAt;
    int stage;
};

namespace Bombs {
    Bomb bombs[BOMBS_AMOUNT];

    /**
     * Este método retorna se uma bomba está colocada no mapa
     * @param index Índice da bomba
     * @return Se a bomba está colocada
     */
    bool isBombPlaced(int index) {
        return bombs[index].placed;
    }

    /**
     * Este método retorna o estágio de explosão que uma bomba está
     * @param index Índice da bomba
     * @return Qual estagio da explosão está a bomba
     */
    int getBombStage(int index) {
        return bombs[index].stage;
    }

    /**
     * Este método verifica se uma bomba está perto de uma localização
     * @param bomb Bomba para verificar
     * @param row Linha da localização
     * @param column Coluna da localização
     * @return Uma boolean se a bomba está perto
     */
    bool isBombNearToCoordinates(Bomb bomb, int row, int column) {
        bool thereIsAbove = (bomb.row == row - 1) && bomb.column == column;
        bool thereIsBelow = (bomb.row == row + 1) && bomb.column == column;
        bool thereIsOnLeft = bomb.row == row && (bomb.column == column - 1);
        bool thereIsOnRight = bomb.row == row && (bomb.column == column + 1);
        bool thereIsHere = bomb.row == row && bomb.column == column;

        return thereIsAbove || thereIsBelow || thereIsOnLeft || thereIsOnRight || thereIsHere;
    }

    /**
     * Este método verifica se alguma bomba está perto de uma localização
     * @param row Linha da localização
     * @param column Coluna da localização
     * @return Uma boolean se uma bomba existe perto dessa localização
     */
    bool isBombNear(int row, int column) {
        for (int i = 0; i < BOMBS_AMOUNT; ++i) {
            Bomb currentBomb = bombs[i];

            if (currentBomb.placed) {
                bool isNear = isBombNearToCoordinates(currentBomb, row, column);

                if (isNear) {
                    return true;
                }
            }
        }

        return false;
    }

    /**
     * Este método retorna se uma explosão está ocorrendo perto localização
     * @param row Linha da localização
     * @param column Coluna da localização
     * @return Uma boolean se uma explosão existe perto dessa localização
     */
    bool isExplosionNear(int row, int column) {
        for (int i = 0; i < BOMBS_AMOUNT; ++i) {
            Bomb currentBomb = bombs[i];

            if (currentBomb.placed && currentBomb.stage == 4) {
                bool isNear = isBombNearToCoordinates(currentBomb, row, column);

                if (isNear) {
                    return true;
                }
            }
        }

        return false;
    }

    /**
     * Método para colocar uma bomba no mapa
     * @param row Linha da localização
     * @param column Coluna da localização
     * @param index Índice (identificador) da bomba
     */
    void placeBomb(int row, int column, int index) {
        if (isBombPlaced(index)) return;

        Bomb bomb {};

        bomb.row = row;
        bomb.column = column;
        bomb.placed = true;
        bomb.stage = 1;
        bomb.placedAt = clock();

        bombs[index] = bomb;
    }

    /**
     * Método para inicializar o array de bombas
     */
    void initBombsArray() {
        for (int i = 0; i < BOMBS_AMOUNT; ++i) {
            Bomb bomb {};

            bomb.row = 0;
            bomb.column = 0;
            bomb.placed = false;

            bombs[i] = bomb;
        }
    }

    /**
     * Verifica se existe uma parede frágil na localização, se existir apaga essa parede frágil
     * @param row Linha da localização
     * @param column Coluna da localização
     */
    void breakWall(int row, int column) {
        if (row > 0 && row < MAP_HEIGHT && column > 0 && column < MAP_WIDTH) {
            if (MAP[row][column] == 2) {
                MAP[row][column] = 0;
            }
        }
    }

    /**
     * Deleta as paredes frágeis das laterais de uma bomba
     * @param bomb Bomba
     */
    void removeWallFromNearBomb(Bomb bomb) {
        breakWall(bomb.row + 1, bomb.column);
        breakWall(bomb.row - 1, bomb.column);
        breakWall(bomb.row, bomb.column + 1);
        breakWall(bomb.row, bomb.column - 1);
    }

    /**
     * Método responsável pela lógica das bombas (roda no Loop principal)
     */
    void tick() {
        for (int i = 0; i < BOMBS_AMOUNT; ++i) {
            Bomb current = bombs[i];

            // Se a bomba está colocada no mapa, muda o estágio dela
            if (current.placed) {
                int end = clock();

                int currentTime = (end - current.placedAt) / CLOCKS_PER_SEC;

                // O estágio da bomba é basicamente o tempo que ela está colocada
                current.stage = currentTime + 1;

                // Estágio de explosão
                if (current.stage == 4) {
                    removeWallFromNearBomb(current);
                }

                // Reseta a bomba para o estagio inicial
                if (current.stage > 4) {
                    current.stage = 0;
                    current.placed = false;
                }

                // Atualiza a bomba no Array principal
                bombs[i] = current;
            }
        }
    }

    /**
     * Método responsável pela lógica de renderização (roda no Loop principal)
     * @param row Linha que está percorrendo
     * @param column Coluna que está percorrendo
     * @return Retorna TRUE se for para escrever o simbolo da bomba no mapa
     */
    bool render(int row, int column) {
        for (int i = 0; i < BOMBS_AMOUNT; ++i) {
            Bomb current = bombs[i];

            if (!current.placed) continue;

            // Verifica se a bomba está perto das coordenadas
            // E muda a cor do fundo do console conforme o estado da explosão
            if (isBombNearToCoordinates(current, row, column)) {
                if (current.stage == 1) {
                    ConsoleColor::showColor(Color::RED_BACKGROUND);
                }
                if (current.stage == 2) {
                    ConsoleColor::showColor(Color::YELLOW_BACKGROUND);
                }
                if (current.stage == 3) {
                    ConsoleColor::showColor(Color::ORANGE_BACKGROUND);
                }
                if (current.stage == 4) {
                    ConsoleColor::showColor(Color::WHITE_BACKGROUND);
                }
            }

            if (current.row == row && current.column == column) {
                return true;
            }
        }

        return false;
    }
}

#endif //GAME02_BOMBS_H
