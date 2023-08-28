//
// Created by Caio on 25/08/2023.
//

#ifndef GAME02_PLAYER_H
#define GAME02_PLAYER_H

#include <iostream>
#include "./enums/GameChar.h"

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

    }

    /**
     * Camada de lógica do jogador, por exemplo, movimentação, colocar bombas...
     * @param pressedKey Informa qual tecla foi pressionada, informações úteis:
     * - W = 119
     * - S = 115
     * - A = 975
     * - D = 100
     * - Espaço = 320
     * - Seta para cima = 724
     * - Seta para baixo = 804
     * - Seta para direita = 754
     * - Seta para esquerda = 774
     */
    void tick(int pressedKey) {
        switch(pressedKey){
            case 724 //|| case 119cima
                row--;
                bool canMove();
            break;

            case 804 //|| case 115 //baixo
                row++;
                bool canMove();
            break;

            case 774 //|| case 975 //esquerda
                column--;
                bool canMove();
            break;

            case 754 //|| case 100 //direita
                column++;
                bool canMove();
            break;
        }
    }

    /**
     * Este método deve apenas retornar o  atual do jogador
     */
    char render() {
        return char(GameChar::PLAYER);
    }
}

#endif //GAME02_PLAYER_H