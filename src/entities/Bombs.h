//
// Created by Caio on 25/08/2023.
//

#ifndef GAME02_BOMBS_H
#define GAME02_BOMBS_H

#include <cmath>
#include "../utils/ConsoleColors.h"
#include "../enums/GameChar.h"
#include "../managers/MapManager.h"
#include "../utils/Vector.h"
#include "../GameStatistics.h"

struct Bomb {
    int row;
    int column;
    clock_t placedAt;
    int stage;
    bool isFromPlayer;
    bool ignoreWalls;
    int radius;
};

namespace Bombs {
    Vector<Bomb> bombs;

    // Função para determinar a direção de um objeto em relação a uma localização
    vector<int> getDirectionToBomb(Bomb bomb, int row, int column) {
        // Calcular a diferença entre as coordenadas x e y do objeto e da localização
        double dy = bomb.row - row;
        double dx = bomb.column - column;

        // Determinar a direção com base na diferença entre as coordenadas
        int directionColumn = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
        int directionRow = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);

        return { directionRow, directionColumn };
    }

    /**
     * Este método verifica se uma bomba está perto de uma localização
     * @param bomb Bomba para verificar
     * @param row Linha da localização
     * @param column Coluna da localização
     * @return Uma boolean se a bomba está perto
     */
    bool isBombNearToCoordinates(Bomb bomb, int row, int column) {
        int directions[][2] = { {0, 1}, {0, -1}, { 1, 0 }, { -1, 0 } };

        for (int i = 0; i < 4; ++i) {
            for (int j = 1; j <= bomb.radius; ++j) {
                int directionRow = directions[i][0] * j;
                int directionColumn = directions[i][1] * j;

                int targetRow = bomb.row + directionRow;
                int targetColumn = bomb.column + directionColumn;

                // Se a bomba não ignora paredes, deve verificar se existe uma parede entre a bomba
                if (!bomb.ignoreWalls && !(bomb.row == row && bomb.column == column)) {
                    if (MapManager::currentMap.getTiles()[row][column] == 1) return false;

                    // Pega a direção que deve seguir
                    vector<int> directionToBomb = getDirectionToBomb(bomb, row, column);

                    // Verificar se existe uma parede entre
                    if (MapManager::currentMap.getTiles()[row + directionToBomb[0]][column + directionToBomb[1]] == 1) return false;
                }

                if ((targetRow) == row && (targetColumn) == column) return true;
            }
        }

        return bomb.row == row && bomb.column == column;
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
    void placeBomb(int row, int column, bool isPlayer = false, int radius = 1, bool ignoreWalls = false) {
        if (isPlayer && isThereBombPlacedByPlayer()) return;

        if (isPlayer) {
            GameStatistics::amountOfBombsPlaced++;
        }

        Bomb bomb {};

        bomb.row = row;
        bomb.column = column;
        bomb.stage = 1;
        bomb.radius = radius;
        bomb.placedAt = clock();
        bomb.isFromPlayer = isPlayer;
        bomb.ignoreWalls = ignoreWalls;

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
        int directions[][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < bomb.radius; ++j) {
                int directionRow = directions[i][0] == 0 ? 0 : directions[i][0] * (j + 1);
                int directionColumn = directions[i][1] == 0 ? 0 : directions[i][1] * (j + 1);

                int targetRow = bomb.row + directionRow;
                int targetColumn = bomb.column + directionColumn;

                // Pega a direção que deve seguir
                vector<int> directionToBomb = getDirectionToBomb(bomb, targetRow, targetColumn);

                // Verificar se existe uma parede entre
                if (MapManager::currentMap.getTiles()[targetRow + directionToBomb[0]][targetColumn + directionToBomb[1]] == 1) {
                    // Existe uma parede entre, não remova a parede
                    break;
                } else {
                    // Não há parede entre, remova a parede
                    breakWall(targetRow, targetColumn);
                }
            }
        }
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
    bool render(int row, int column, Color &color, BackgroundColor &bgColor) {
        for (int i = 0; i < bombs.getSize(); ++i) {
            Bomb current = bombs[i];

            // Verifica se a bomba está perto das coordenadas
            // E muda a cor do fundo do console conforme o estado da explosão
            if (isBombNearToCoordinates(current, row, column)) {
                color = Color::WHITE;
                if (current.stage == 1) {
                    bgColor = BackgroundColor::RED;
                }
                if (current.stage == 2) {
                    bgColor = BackgroundColor::YELLOW;
                }
                if (current.stage == 3) {
                    bgColor = BackgroundColor::OLIVE;
                }
                if (current.stage == 4) {
                    color = Color::BLACK;
                    bgColor = BackgroundColor::WHITE;
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
