//
// Created by Caio on 25/08/2023.
//

#ifndef GAME02_BOMBS_H
#define GAME02_BOMBS_H

#include "../utils/ConsoleColors.h"
#include "../enums/GameChar.h"
#include "../managers/MapManager.h"
#include "../utils/Vector.h"
#include "../GameStatistics.h"
#include <time.h>

struct Bomb {
    int row;
    int column;
    clock_t placedAt;
    int stage;
    bool isFromPlayer;
};

namespace Bombs {
    Vector<Bomb> bombs;

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
        for (int i = 0; i < bombs.getSize(); ++i) {
            Bomb currentBomb = bombs[i];

            bool isNear = isBombNearToCoordinates(currentBomb, row, column);

            if (isNear) {
                return true;
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
        for (int i = 0; i < bombs.getSize(); ++i) {
            Bomb currentBomb = bombs[i];

            if (currentBomb.stage == 4) {
                bool isNear = isBombNearToCoordinates(currentBomb, row, column);

                if (isNear) {
                    return true;
                }
            }
        }

        return false;
    }

    bool isThereBombPlacedByPlayer() {
        for (int i = 0; i <  bombs.getSize(); ++i) {
            if (bombs[i].isFromPlayer) return true;
        }

        return false;
    }

    /**
     * Método para colocar uma bomba no mapa
     * @param row Linha da localização
     * @param column Coluna da localização
     * @param index Índice (identificador) da bomba
     */
    void placeBomb(int row, int column, bool isPlayer = false) {
        if (isPlayer && isThereBombPlacedByPlayer()) return;

        if (isPlayer) {
            GameStatistics::amountOfBombsPlaced++;
        }

        Bomb bomb {};

        bomb.row = row;
        bomb.column = column;
        bomb.stage = 1;
        bomb.placedAt = clock();
        bomb.isFromPlayer = isPlayer;

        bombs.push(bomb);
    }

    /**
     * Verifica se existe uma parede frágil na localização, se existir apaga essa parede frágil
     * @param row Linha da localização
     * @param column Coluna da localização
     */
    void breakWall(int row, int column) {
        if (MapManager::validLocation(row, column)) {
            if (MapManager::currentMap.getTiles()[row][column] == 2) {
                MapManager::currentMap.getTiles()[row][column] = 0;
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
        for (int i = 0; i < bombs.getSize(); ++i) {
            Bomb current = bombs[i];

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
                bombs.remove(i);
                continue;
            }

            // Atualiza a bomba no Array principal
            bombs[i] = current;
        }
    }

    /**
     * Método responsável pela lógica de renderização (roda no Loop principal)
     * @param row Linha que está percorrendo
     * @param column Coluna que está percorrendo
     * @return Retorna TRUE se for para escrever o simbolo da bomba no mapa
     */
    bool render(int row, int column) {
        for (int i = 0; i < bombs.getSize(); ++i) {
            Bomb current = bombs[i];

            // Verifica se a bomba está perto das coordenadas
            // E muda a cor do fundo do console conforme o estado da explosão
            if (isBombNearToCoordinates(current, row, column)) {
                if (current.stage == 1) {
                    ConsoleColor::set(Color::LIGHTGRAY, BackgroundColor::RED);
                }
                if (current.stage == 2) {
                    ConsoleColor::set(Color::LIGHTGRAY, BackgroundColor::YELLOW);
                }
                if (current.stage == 3) {
                    ConsoleColor::set(Color::LIGHTGRAY, BackgroundColor::OLIVE);
                }
                if (current.stage == 4) {
                    ConsoleColor::set(Color::LIGHTGRAY, BackgroundColor::WHITE);
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
