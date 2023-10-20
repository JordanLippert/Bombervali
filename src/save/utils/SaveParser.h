//
// Created by Caio on 19/10/2023.
//

#ifndef GAME02_CBP_SAVEPARSER_H
#define GAME02_CBP_SAVEPARSER_H

#include <utility>

#include "../../entities/Save.h"
#include "../../GameStatistics.h"
#include "../../entities/Enemies.h"
#include "../../entities/Consumables.h"
#include "../../entities/Bombs.h"

namespace SaveParser {
    Save createFromGame(string saveName, int pRow, int pColumn, int pBombs) {
        int playerRow = pRow;
        int playerColumn = pColumn;
        int bombsAmountOfPlayer = pBombs;

        Save save(PlayerInfo(playerRow, playerColumn, bombsAmountOfPlayer));

        save.placedBombs = GameStatistics::amountOfBombsPlaced;
        save.gameTime = GameStatistics::gameTime;
        save.enemiesAmount = Enemies::enemies.getSize();
        save.currentLevel = MapManager::currentLevel;
        save.map = MapManager::currentMap;
        save.saveName = std::move(saveName);

        for (int i = 0; i < Enemies::enemies.getSize(); ++i) {
            Enemy currentEnemy = Enemies::enemies[i];

            SaveEnemy newSaveEnemy(currentEnemy.row, currentEnemy.column);

            save.enemies.push_back(newSaveEnemy);
        }

        for (int i = 0; i < Consumables::consumables.getSize(); ++i) {
            Consumable current = Consumables::consumables[i];

            SaveConsumable newSaveConsumable(current.row, current.column, current.type);

            save.consumables.push_back(newSaveConsumable);
        }

        for (int i = 0; i < Bombs::bombs.getSize(); ++i) {
            Bomb current = Bombs::bombs[i];

            SaveBomb newSaveBomb(current.row, current.column, current.stage, current.isFromPlayer, current.ignoreWalls, current.radius, current.placedAt);

            save.bombs.push_back(newSaveBomb);
        }

        return save;
    }
}

#endif //GAME02_CBP_SAVEPARSER_H
