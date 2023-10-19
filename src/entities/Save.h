//
// Created by Caio on 18/10/2023.
//

#ifndef GAME02_CBP_SAVE_H
#define GAME02_CBP_SAVE_H

#include "../enums/ConsumableType.h"
#include "../utils/Vector.h"
#include "Bombs.h"

class PlayerInfo {
    int row, column, bombsAmount;

    PlayerInfo(int row, int column, int bombsAmount) {
        this->row = row;
        this->column = column;
        this->bombsAmount = bombsAmount;
    }
};

class SaveEnemy {
    int row, column;

    SaveEnemy(int row, int column) {
        this->row = row;
        this->column = column;
    }
};

class SaveConsumable {
    int row, column;
    ConsumableType type;

    SaveEnemy(int row, int column) {
        this->row = row;
        this->column = column;
    }
};

class Save {
    string saveName;
    int currentLevel;
    int gameTime;
    int placedBombs;
    int enemiesAmount;
    PlayerInfo playerInfo;
    Vector<SaveEnemy> enemies;
    Vector<SaveConsumable> consumables;
    Vector<Bomb> bombs;
};

#endif //GAME02_CBP_SAVE_H
