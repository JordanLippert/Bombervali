//
// Created by Caio on 27/08/2023.
//

#ifndef GAME02_CONFIG_H
#define GAME02_CONFIG_H

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int MAP_HEIGHT = 21;
const int MAP_WIDTH = 21;
const int ENEMIES_AMOUNT = 3;
const int BOMBS_AMOUNT = ENEMIES_AMOUNT + 1;

int MAP[MAP_HEIGHT][MAP_WIDTH];

void writeMap() {
    ofstream file;

    file.open("../assets/map.txt");

    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            file << MAP[i][j];

            if (j < MAP_WIDTH - 1) {
                file << ",";
            }
        }

        file << "\n";
    }
}

void loadMap() {
    ifstream file;

    file.open("../assets/map.txt");

    int row = 0;

    string currentLine;
    while (!file.eof()) {
        getline(file, currentLine);

        stringstream stream(currentLine);

        int column = 0;
        string currentString;

        while (getline(stream, currentString, ',')){
            int mapValue = stoi(currentString);

            MAP[row][column] = mapValue;
            column++;
        }
        row++;
    }
}

const int HUD_SIZE = 3;

std::string HUD[HUD_SIZE] = {
        "Faltam $enimies inimigos serem mortos",
        "$bar            "
};

bool canMove(int row, int column) {
    if (row < 0 || row >= MAP_HEIGHT || column < 0 || column >= MAP_WIDTH) return false;

    int mapValue = MAP[row][column];

    return mapValue != 1 && mapValue != 2;
}

#endif //GAME02_CONFIG_H
