//
// Created by Caio on 25/08/2023.
//

#ifndef GAME02_PLAYER_H
#define GAME02_PLAYER_H

#include <iostream>
#include "../enums/GameChar.h"
#include "Bombs.h"
#include "../Menu.h"

using namespace std;

namespace Player {
    // Localização do jogador, row = linha, column = coluna
    int row = 1, column = 1;

    /**
     * Este método retorna se o player está em uma posição específica
     */
    bool isInPosition(int arrayRow, int arrayColumn) {
        return row == arrayRow && column == arrayColumn;
    }

    /**
     * Este método deve ser acionado quando a pessoa pressionar Espaço (Deixe ele me branco, apenas chame ele)
     */
    void placeBomb() {
        Bombs::placeBomb(row, column, 3);
    }

    /**
     * Camada de lógica do jogador, por exemplo, movimentação, colocar bombas...
     * @param pressedKey Informa qual tecla foi pressionada, informações úteis:
     * - W = 11
     * - S = 11
     * - A = 97
     * - D = 10
     * - Espaço = 32
     * - Seta para cima = 72
     * - Seta para baixo = 80
     * - Seta para direita = 75
     * - Seta para esquerda = 77
     */
    void tick(int pressedKey) {
        if(Bombs::isExplosionNear(row, column) || Enemies::thereIsEnemy(row, column)) /** Controle de morte do Player */
        {
            Menu:: changeState(GameStage::LOSE);
        }

        switch(pressedKey){
            case 72: case 'w': /** cima */
                if(MapManager::canMove(row - 1 , column)){
                    row--;
                }
                break;

            case 80: case 's': /** baixo */
                if(MapManager::canMove(row + 1 , column)){
                    row++;
                }
                break;

            case 75: case 'a': /** esquerda */
                if(MapManager::canMove(row, column - 1)){
                    column--;
                }
                break;

            case 77: case 'd': /** direita */
                if(MapManager::canMove(row, column + 1)){
                    column++;
                }
                break;

            case 32: case 13: /** dropar bomba */
                placeBomb();
                break;
        }
    }

    /**
     * Este método deve apenas retornar o local atual do jogador
     */
    char render() {
        return char(GameChar::PLAYER);
    }
}

#endif //GAME02_PLAYER_H
