//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_MAPMANAGER_H
#define GAME02_CBP_MAPMANAGER_H

#include "../map/GameMap.h"
#include "../map/utils/MapReader.h"
#include "../utils/Path.h"

namespace MapManager {
    GameMap currentMap;
    int currentLevel = 1;

    const int MAX_LEVEL = 3;

    /**
     * Carrega um nível do jogo com base no número do nível.
     * @param level O número do nível a ser carregado.
     */
    void loadLevel(int level) {
        string levelName = "../assets/maps/level_" + to_string(level) + ".csv";
        currentMap = MapReader::readFromFile(levelName);
    }

    /**
     * Verifica se uma localização (linha e coluna) está dentro dos limites do mapa.
     * @param row A linha da localização.
     * @param column A coluna da localização.
     * @return Retorna true se a localização estiver dentro dos limites do mapa, senão, retorna false.
     */
    bool validLocation(int row, int column) {
        return !(row < 0 || row >= currentMap.getRows() || column < 0 || column >= currentMap.getColumns());
    }

    /**
     * Verifica se é possível mover-se para uma localização específica no mapa.
     * @param row A linha da localização.
     * @param column A coluna da localização.
     * @return Retorna true se for possível mover-se para a localização, senão, retorna false.
     */
    bool canMove(int row, int column) {
        if (!validLocation(row, column)) return false;

        int mapValue = currentMap.getTiles()[row][column];

        return mapValue != 1 && mapValue != 2;
    }
}

#endif //GAME02_CBP_MAPMANAGER_H
