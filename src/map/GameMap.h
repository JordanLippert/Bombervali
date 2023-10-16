//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_GAMEMAP_H
#define GAME02_CBP_GAMEMAP_H

#include "../utils/Vector.h"

struct GameMap {
    int rows, columns;
    Vector<Vector<int>> tiles;
};

#endif //GAME02_CBP_GAMEMAP_H
