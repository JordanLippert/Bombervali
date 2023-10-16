//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_MAPMANAGER_H
#define GAME02_CBP_MAPMANAGER_H

#include "GameMap.h"
#include "utils/MapReader.h"
#include "../utils/Path.h"

namespace MapManager {
    GameMap currentMap;
    int currentLevel = 1;

    void loadLevel(int level) {
        string levelName = "../assets/maps/level_";

        levelName += to_string(level);
        levelName += ".csv";

        currentMap = MapReader::readFromFile(levelName);
    }

    bool validLocation(int row, int column) {
        return !(row < 0 || row >= currentMap.getRows() || column < 0 || column >= currentMap.getColumns());
    }

    bool canMove(int row, int column) {
        if (!validLocation(row, column)) return false;

        int mapValue = currentMap.getTiles()[row][column];

        return mapValue != 1 && mapValue != 2;
    }
}

#endif //GAME02_CBP_MAPMANAGER_H
