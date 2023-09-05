//
// Created by Caio on 27/08/2023.
//

#ifndef GAME02_CONFIG_H
#define GAME02_CONFIG_H

const int MAP_HEIGHT = 21;
const int MAP_WIDTH = 21;
const int ENEMIES_AMOUNT = 3;
const int BOMBS_AMOUNT = ENEMIES_AMOUNT + 1;

int MAP[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 2, 2, 1, 0, 2, 0, 2, 1, 1, 2, 0, 0, 1, 2, 2, 0, 0, 1},
        {1, 0, 1, 0, 0, 2, 2, 0, 1, 2, 1, 1, 2, 1, 2, 2, 0, 0, 1, 0, 1},
        {1, 2, 0, 1, 0, 0, 2, 2, 1, 0, 0, 2, 0, 1, 2, 0, 0, 1, 0, 2, 1},
        {1, 2, 0, 0, 2, 1, 2, 0, 2, 2, 1, 2, 2, 0, 2, 1, 2, 0, 0, 2, 1},
        {1, 1, 2, 2, 2, 2, 1, 2, 1, 0, 2, 0, 1, 2, 1, 2, 2, 2, 2, 1, 1},
        {1, 0, 0, 1, 0, 1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 2, 1, 2, 2, 1, 0, 1, 2, 2, 1, 2, 1, 0, 1, 0, 1},
        {1, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 1},
        {1, 1, 2, 0, 1, 0, 2, 0, 1, 1, 0, 1, 1, 0, 2, 0, 1, 0, 2, 1, 1},
        {1, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 1},
        {1, 1, 2, 0, 1, 0, 2, 2, 1, 1, 0, 1, 1, 2, 2, 0, 1, 0, 2, 1, 1},
        {1, 0, 2, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 0, 2, 0, 2, 0, 2, 0, 1},
        {1, 0, 1, 0, 1, 2, 1, 0, 2, 1, 0, 1, 2, 0, 1, 2, 1, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 2, 2, 0, 0, 0, 2, 2, 0, 1, 0, 1, 0, 0, 1},
        {1, 1, 2, 2, 2, 2, 1, 1, 1, 0, 2, 0, 1, 1, 1, 2, 2, 2, 2, 1, 1},
        {1, 2, 0, 0, 2, 1, 2, 0, 2, 2, 1, 2, 2, 0, 2, 1, 2, 0, 0, 2, 1},
        {1, 2, 0, 1, 0, 0, 2, 2, 1, 0, 0, 2, 0, 1, 2, 0, 0, 1, 0, 2, 1},
        {1, 0, 1, 0, 0, 2, 2, 0, 1, 2, 1, 1, 2, 1, 2, 2, 0, 0, 1, 0, 1},
        {1, 0, 0, 2, 2, 1, 0, 2, 0, 2, 1, 1, 2, 0, 0, 1, 2, 2, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

const int HUD_SIZE = 3;

std::string HUD[HUD_SIZE] = {
        "Faltam $enimies serem mortos",
        "$bar            "
};

bool canMove(int row, int column) {
    if (row < 0 || row >= MAP_HEIGHT || column < 0 || column >= MAP_WIDTH) return false;

    int mapValue = MAP[row][column];

    return mapValue != 1 && mapValue != 2;
}

#endif //GAME02_CONFIG_H
