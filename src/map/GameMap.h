//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_GAMEMAP_H
#define GAME02_CBP_GAMEMAP_H

#include <vector>

using namespace std;

class GameMap {
private:
    int rows, columns;
    vector<vector<int>> tiles;

public:
    GameMap() {
        this->rows = 0;
        this->columns = 0;
    }

    GameMap(int rows, int columns, vector<vector<int>> tiles) {
        this->rows = rows;
        this->columns = columns;
        this->tiles = std::move(tiles);
    }

    vector<vector<int>>& getTiles() {
        return this->tiles;
    }

    int getRows() const {
        return this->rows;
    }

    int getColumns() const {
        return this->rows;
    }
};

#endif //GAME02_CBP_GAMEMAP_H
