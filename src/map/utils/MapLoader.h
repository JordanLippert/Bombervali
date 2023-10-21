//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_MAPLOADER_H
#define GAME02_CBP_MAPLOADER_H

#include "../GameMap.h"
#include "../../entities/Player.h"
#include "../../entities/Enemies.h"
#include "../PlayerLocation.h"
#include "../../entities/Consumables.h"

namespace MapLoader {
    /**
     * Carrega o jogo a partir de um mapa, reinicializando as listas de bombas, inimigos e consumíveis.
     * @param map O mapa a partir do qual o jogo será carregado.
     */
    void loadGameFromMap(GameMap map) {
        Bombs::bombs.clear();
        Enemies::enemies.clear();
        Consumables::consumables.clear();

        for (int i = 0; i < map.getRows(); ++i) {
            for (int j = 0; j < map.getColumns(); ++j) {
                int tileType = map.getTiles()[i][j];

                if (tileType > 2) {
                    switch (tileType) {
                        case 3: {
                            // Player
                            PlayerLocation::row = i;
                            PlayerLocation::column = j;
                            PlayerLocation::reset = true;
                            break;
                        }
                        case 4: {
                            // Inimigo
                            Enemy newEnemy {};

                            newEnemy.row = i;
                            newEnemy.column = j;
                            newEnemy.hasPlacedBomb = false;

                            Enemies::enemies.push(newEnemy);
                            break;
                        }
                        case 5: {
                            // Consumivel Bomba
                            Consumables::placeNew(i, j, ConsumableType::BOMB);
                            break;
                        }
                        case 6: {
                            // Consumivel Power Up - Distância de explosão
                            Consumables::placeNew(i, j, ConsumableType::POWER_UP_DISTANCE);
                            break;
                        }
                        case 7: {
                            // Consumivel Power Up - Atravessar paredes
                            Consumables::placeNew(i, j, ConsumableType::POWER_UP_IGNORE_WALLS);
                            break;
                        }
                    }
                }
            }
        }
    }
}

#endif //GAME02_CBP_MAPLOADER_H
