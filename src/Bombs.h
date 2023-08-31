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
     * @param index Indice da bomba
     * @return Se a bomba está colocada
     */
    bool isBombPlaced(int index) {
        return bombs[index].placed;
    }

    bool isBombNearToCoordinates(Bomb bomb, int row, int column) {
        bool thereIsAbove = (bomb.row == row - 1) && bomb.column == column;
        bool thereIsBelow = (bomb.row == row + 1) && bomb.column == column;
        bool thereIsOnLeft = bomb.row == row && (bomb.column == column - 1);
        bool thereIsOnRight = bomb.row == row && (bomb.column == column + 1);
        bool thereIsHere = bomb.row == row && bomb.column == column;

        return thereIsAbove || thereIsBelow || thereIsOnLeft || thereIsOnRight || thereIsHere;
    }

    bool isExplosionNear(int row, int column) {
        for (int i = 0; i < BOMBS_AMOUNT; ++i) {
            Bomb currentBomb = bombs[i];

            if (currentBomb.placed && currentBomb.stage == 3) {
                return true;
            }
        }

        return false;
    }

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

    void initBombsArray() {
        for (int i = 0; i < BOMBS_AMOUNT; ++i) {
            Bomb bomb {};

            bomb.row = 0;
            bomb.column = 0;
            bomb.placed = false;

            bombs[i] = bomb;
        }
    }

    bool breakWall(int row, int column) {
        if (row > 0 && row < MAP_HEIGHT && column > 0 && column < MAP_WIDTH) {
            if (MAP[row][column] == 2) {
                MAP[row][column] = 0;
            }
        }

        return false;
    }

    void removeWallFromNearBomb(Bomb bomb) {
        breakWall(bomb.row + 1, bomb.column);
        breakWall(bomb.row - 1, bomb.column);
        breakWall(bomb.row, bomb.column + 1);
        breakWall(bomb.row, bomb.column - 1);
    }

    void tick() {
        for (int i = 0; i < BOMBS_AMOUNT; ++i) {
            Bomb current = bombs[i];

            if (current.placed) {
                int end = clock();

                int currentTime = (end - current.placedAt) / CLOCKS_PER_SEC;

                current.stage = currentTime + 1;

                if (current.stage == 4) {
                    removeWallFromNearBomb(current);
                }

                if (current.stage > 4) {
                    current.stage = 0;
                    current.placed = false;
                }

                bombs[i] = current;
            }
        }
    }

    bool render(int row, int column) {
        for (int i = 0; i < BOMBS_AMOUNT; ++i) {
            Bomb current = bombs[i];

            if (!current.placed) continue;

            if (MAP[row][column] != 1 && isBombNearToCoordinates(current, row, column)) {
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
