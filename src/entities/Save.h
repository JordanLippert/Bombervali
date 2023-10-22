//
// Created by Caio on 18/10/2023.
//

#ifndef GAME02_CBP_SAVE_H
#define GAME02_CBP_SAVE_H

#include <string>
#include "../enums/ConsumableType.h"
#include "../map/GameMap.h"

class PlayerInfo {
public:
    int row, column, bombsAmount, specialbomb1, specialbomb2;

    PlayerInfo(int row, int column, int bombsAmount, int specialbomb1, int specialbomb2) {
        this->row = row;
        this->column = column;
        this->bombsAmount = bombsAmount;
        this->specialbomb1 = specialbomb1;
        this->specialbomb2 = specialbomb2;
    }
};

class SaveEnemy {
public:
    int row, column;

    SaveEnemy(int row, int column) {
        this->row = row;
        this->column = column;
    }
};

class SaveConsumable {
public:
    int row, column;
    ConsumableType type;

    SaveConsumable(int row, int column, ConsumableType type) {
        this->row = row;
        this->column = column;
        this->type = type;
    }
};

class SaveBomb {
public:
    int row, column, stage, isFromPlayer, ignoreWalls, radius;

    SaveBomb(int row, int column, int stage, int isFromPlayer, int ignoreWalls, int radius) {
        this->row = row;
        this->column = column;
        this->stage = stage;
        this->isFromPlayer = isFromPlayer;
        this->ignoreWalls = ignoreWalls;
        this->radius = radius;
    }
};

class Save {
public:
    string saveName;
    int currentLevel {};
    int gameTime {};
    int saveNumber {};
    int placedBombs {};
    int enemiesAmount {};
    PlayerInfo playerInfo;
    vector<SaveEnemy> enemies;
    vector<SaveConsumable> consumables {};
    vector<SaveBomb> bombs {};
    GameMap map;

    Save(PlayerInfo playerInfo) : playerInfo(playerInfo) {}
};

#endif //GAME02_CBP_SAVE_H
