//
// Created by Caio on 20/10/2023.
//

#ifndef GAME02_CBP_SAVELOADER_H
#define GAME02_CBP_SAVELOADER_H

#include "../../entities/Save.h"
#include "../../map/PlayerLocation.h"
#include "../../entities/Enemies.h"
#include "../../entities/Consumables.h"
#include "../../entities/Bombs.h"

namespace SaveLoader {
    void loadIntoGame(Save save) {
        PlayerLocation::reset = true;
        PlayerLocation::row = save.playerInfo.row;
        PlayerLocation::column = save.playerInfo.column;
        PlayerLocation::bombsAmount = save.playerInfo.bombsAmount;

        GameStatistics::gameTime = save.gameTime;
        GameStatistics::amountOfBombsPlaced = save.placedBombs;

        Enemies::enemies.clear();
        for (int i = 0; i < save.enemies.size(); ++i) {
            SaveEnemy saveEnemy = save.enemies[i];

            Enemy enemy {};

            enemy.row = saveEnemy.row;
            enemy.column = saveEnemy.column;

            Enemies::enemies.push(enemy);
        }

        Consumables::consumables.clear();
        for (int i = 0; i < save.consumables.size(); ++i) {
            SaveConsumable saveConsumable = save.consumables[i];

            Consumable consumable {};

            consumable.row = saveConsumable.row;
            consumable.column = saveConsumable.column;
            consumable.type = saveConsumable.type;

            Consumables::consumables.push(consumable);
        }

        Bombs::bombs.clear();
        for (int i = 0; i < save.bombs.size(); ++i) {
            SaveBomb saveBomb = save.bombs[i];

            Bomb bomb {};

            bomb.row = saveBomb.row;
            bomb.column = saveBomb.column;
            bomb.stage = saveBomb.stage;
            bomb.isFromPlayer = saveBomb.isFromPlayer;
            bomb.ignoreWalls = saveBomb.ignoreWalls;
            bomb.radius = saveBomb.radius;

            Bombs::bombs.push(bomb);
        }

        MapManager::currentMap = save.map;
        MapManager::currentLevel = save.currentLevel;
    }
}

#endif //GAME02_CBP_SAVELOADER_H
