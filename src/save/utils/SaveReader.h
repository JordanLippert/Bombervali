//
// Created by Caio on 20/10/2023.
//

#ifndef GAME02_CBP_SAVEREADER_H
#define GAME02_CBP_SAVEREADER_H

#include <iostream>
#include <string>
#include <dirent.h>
#include <fstream>
#include "../../utils/StringUtils.h"
#include "../../entities/Save.h"

using namespace std;

namespace SaveReader {
    ConsumableType consumableTypeFromString(string& typeStr) {
        ConsumableType consumableType = ConsumableType::BOMB;

        if (typeStr == "POWER_UP_DISTANCE") {
            consumableType = ConsumableType::POWER_UP_DISTANCE;
        }
        else if (typeStr == "POWER_UP_IGNORE_WALLS") {
            consumableType = ConsumableType::POWER_UP_IGNORE_WALLS;
        }

        return consumableType;
    }

    int findMajorSaveNumber() {
        struct dirent *entry;
        DIR *dp = opendir("../saves");
        int largestSaveNumber = -1;

        if (dp != nullptr) {
            while ((entry = readdir(dp))) {
                string filename = entry->d_name;
                if (filename.find("save_") == 0) {
                    string numberString = filename.substr(5, filename.length() - 9).c_str();

                    int saveNumber = toInt(numberString);
                    if (saveNumber > largestSaveNumber) {
                        largestSaveNumber = saveNumber;
                    }
                }
            }
            closedir(dp);
        } else {
            cout << "Erro ao abrir a pasta de saves." << endl;
        }

        return largestSaveNumber;
    }

    Save read(int saveNumber) {
        string fileName = "../saves/save_" + to_string(saveNumber) + ".csv";

        ifstream file;
        file.open(fileName);

        Save loadedSave(PlayerInfo(0,0,0));
        cout << "FOI 1" << endl;

        string currentLine;
        while (!file.eof()) {
            getline(file, currentLine);

            vector<string> splittedString = splitString(currentLine, ',');
            string type = splittedString[0];

            if (type == "PLAYER_INFO") {
                int row, column, bombsAmount;

                row = toInt(splittedString[1]);
                column = toInt(splittedString[2]);
                bombsAmount = toInt(splittedString[3]);

                PlayerInfo loadedPlayerInfo(row, column, bombsAmount);
                loadedSave.playerInfo = loadedPlayerInfo;
            } else if (type == "ENEMY") {
                int row, column;

                row = toInt(splittedString[1]);
                column = toInt(splittedString[2]);

                SaveEnemy loadedEnemy(row, column);
                loadedSave.enemies.push_back(loadedEnemy);
            } else if (type == "CONSUMABLE") {
                int row, column;

                row = toInt(splittedString[1]);
                column = toInt(splittedString[2]);
                ConsumableType consumableType = consumableTypeFromString(splittedString[3]);

                SaveConsumable loadedConsumable(row, column, consumableType);
                loadedSave.consumables.push_back(loadedConsumable);
            } else if (type == "BOMB") {
                int row, column, stage, isFromPlayer, ignoreWalls, radius;

                row = toInt(splittedString[1]);
                column = toInt(splittedString[2]);
                stage = toInt(splittedString[3]);
                isFromPlayer = toInt(splittedString[4]);
                ignoreWalls = toInt(splittedString[5]);
                radius = toInt(splittedString[6]);

                SaveBomb loadedBomb(row, column, stage, isFromPlayer, ignoreWalls, radius);
                loadedSave.bombs.push_back(loadedBomb);
            } else if (type == "SAVE_INFO") {
                loadedSave.saveName = splittedString[1];
                loadedSave.currentLevel = toInt(splittedString[2]);
                loadedSave.gameTime = toInt(splittedString[3]);
                loadedSave.placedBombs = toInt(splittedString[4]);
                loadedSave.enemiesAmount = toInt(splittedString[5]);
            }
            else if (type == "MAP") {
                int mapRows, mapColumns;


                mapRows = toInt(splittedString[1]);
                mapColumns = toInt(splittedString[2]);

                vector<vector<int>> tiles;

                for (int row = 0; row < mapRows; ++row) {
                    string mapLine;
                    getline(file, mapLine);

                    vector<string> splittedMapLine = splitString(mapLine, ',');
                    vector<int> columnVector;

                    for (int column = 0; column < splittedMapLine.size(); ++column) {
                        string stringValue = splittedMapLine[column];

                        int intValue = toInt(stringValue);

                        columnVector.push_back(intValue);
                    }

                    tiles.push_back(columnVector);
                }
                loadedSave.map = GameMap(mapRows, mapColumns, tiles);

                file.close();

                return loadedSave;
            }
        }

        file.close();

        return loadedSave;
    }
}

#endif //GAME02_CBP_SAVEREADER_H
