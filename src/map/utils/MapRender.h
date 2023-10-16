//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_MAPRENDER_H
#define GAME02_CBP_MAPRENDER_H

#include "../../entities/Bombs.h"
#include "../../entities/Player.h"
#include "../GameMap.h"

namespace MapRender {
    void render(GameMap map) {
        for (int row = 0; row < map.getRows(); row++) {
            for (int column = 0; column < map.getColumns(); column++) {
                // O método das bombas muda o fundo caso necessário e informa se deve escrever o símbolo da bomba no console
                bool needToPrintBomb = Bombs::render(row, column);

                // Verificar se o player está na posição atual, se sim, escrever o símbolo dele
                if (Player::isInPosition(row, column)) {
                    cout << " " << Player::render() << " ";
                    ConsoleColor::reset();
                    continue;
                }

                // Verificar se um inimigo existe na posição atual, se sim, escrever o símbolo dos inimigos
                if (Enemies::thereIsEnemy(row, column)) {
                    cout << " " << char(GameChar::ENEMY) << " ";
                    ConsoleColor::reset();
                    continue;
                }

                int tileType = map.getTiles()[row][column];

                // Caso seja uma parede
                if (tileType == 1) {
                    cout << char(GameChar::WALL) << char(GameChar::WALL) << char(GameChar::WALL);
                    ConsoleColor::reset();
                    continue;
                }

                // Caso seja uma parede frágil
                if (tileType == 2) {
                    cout << char(GameChar::BREAKABLE_WALL) << char(GameChar::BREAKABLE_WALL) << char(GameChar::BREAKABLE_WALL);
                    ConsoleColor::reset();
                    continue;
                }

                // Por último se for um espaço vazio sem bomba, renderizar sem o símbolo
                if (!needToPrintBomb) cout << "   ";
                else std::cout << " " << char(GameChar::BOMB) << " ";

                // Resetar a cor de fundo caso necessário
                ConsoleColor::reset();
            }

            cout << endl;
        }
    }
}

#endif //GAME02_CBP_MAPRENDER_H
