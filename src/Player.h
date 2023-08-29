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
     * - W = 11
     * - S = 11
     * - A = 97
     * - D = 10
     * - Espaço = 320
     * - Seta para cima = 72
     * - Seta para baixo = 80
     * - Seta para direita = 75
     * - Seta para esquerda = 77
     */
    void tick(int pressedKey) {
        switch(pressedKey){
        case 72: case 'w': /** cima */
            if(canMove(row, column)){
                    row--;}
                break;

            case 80: case 's': /** baixo */
                if(canMove(row, column)){
                    row++;}
                break;

            case 75: case 'a': /** esquerda */
                if(canMove(row, column)){
                    column--;}
                break;

            case 77: case 'd': /** direita */
                if(canMove(row, column)){
                    column++;}
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
