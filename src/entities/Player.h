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
    int row = -1, column = -1;
    int bombsAmount = 5;
    int specialbomb1 = 0;
    int specialbomb2 = 0;

    /**
     * Este método retorna se o player está em uma posição específica
     */
    bool isInPosition(int arrayRow, int arrayColumn) {
        return row == arrayRow && column == arrayColumn;
    }

    /**
     * Este método deve ser acionado quando a pessoa pressionar Espaço ou Enter (Deixe ele em branco, apenas chame ele)
     */
    void placeBomb() {
        // Método para verificar se o player pode colocar uma bomba: Bombs::isThereBombPlacedByPlayer()
        // Remover 1 bomba do player pra cada bomba colocada.

        if (Bombs::isThereBombPlacedByPlayer()) return;

        if(bombsAmount > 0) {
            int radius = 1;
            bool ignoreWalls = false;

            if (specialbomb1 > 0) {
                radius = 2;
                ignoreWalls = false;
                specialbomb1--;
            }

            if (specialbomb2 > 0) {
                radius = 2;
                ignoreWalls = true;
                specialbomb2--;
            }

            Bombs::placeBomb(row, column, true, 1, false);
            bombsAmount--;
        }
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
            Menu::loseGame();
        }

        if(Consumables::existsConsumableAtLocation(row, column)){

            Consumable consumivel = Consumables::getConsumableByLocation(row, column);

            if(consumivel.type == ConsumableType::BOMB){
                bombsAmount = bombsAmount + 3;
            }

            if(consumivel.type == ConsumableType::POWER_UP_DISTANCE){
                specialbomb1 = specialbomb1 + 3;
            }

            if(consumivel.type == ConsumableType::POWER_UP_IGNORE_WALLS){
                specialbomb2 = specialbomb2 + 3;
            }

            Consumables::deleteConsumableByLocation(row, column);
        }

        // verificar consumiveis aqui
        // para verificar se existe um consumível em uma localização, usar: Consumables::existsConsumableAtLocation(linha, coluna)
        // Paga pegar o consumível nessa localização, usar: Consumables::getConsumableByLocation(linha, coluna)
        // Paga remover o consumível do mapa, usar: Consumables::deleteConsumableByLocation(linha, coluna)
        // Boa sorte, lembrando q precisas criar variáveis dentro do Player, para controlar se os powerups de distância e etc estão ativos
        // Para cada bomba coletada, deve aumentar em 1 o número de bombas do player

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
