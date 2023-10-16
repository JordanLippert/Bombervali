//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_MAPLOADER_H
#define GAME02_CBP_MAPLOADER_H

#include "../GameMap.h"
#include "../../entities/Player.h"
#include "../../entities/Enemies.h"
#include "../PlayerLocation.h"

namespace MapLoader {
    void loadGameFromMap(GameMap map) {
        for (int i = 0; i < map.getRows(); ++i) {
            for (int j = 0; j < map.getColumns(); ++j) {
                int tileType = map.getTiles()[i][j];

                if (tileType > 2) {
                    switch (tileType) {
                        case 3:
                            // Player
                            PlayerLocation::row = i;
                            PlayerLocation::column = j;
                            break;
                        case 4:
                            // Inimigo
                            Enemy newEnemy {};

                            newEnemy.row = i;
                            newEnemy.column = j;
                            newEnemy.isLive = true;
                            newEnemy.hasPlacedBomb = false;

                            Enemies::enemies.push(newEnemy);
                            break;
//                        case 5:
//                            // Consumivel Bomba
//                            break;
//                        case 6:
//                            // Consumivel Power Up - Distância de explosão
//                            break;
//                        case 7:
//                            // Consumivel Power Up - Atravessar paredes
//                            break;
                    }
                }
            }
        }
    }
}

#endif //GAME02_CBP_MAPLOADER_H
