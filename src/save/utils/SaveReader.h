//
// Created by Caio on 20/10/2023.
//

#ifndef GAME02_CBP_SAVEREADER_H
#define GAME02_CBP_SAVEREADER_H

#include <iostream>
#include <string>
#include <dirent.h>
#include <fstream>
#include <filesystem>
#include "../../utils/StringUtils.h"
#include "../../entities/Save.h"

using namespace std;

namespace SaveReader {
    /**
     * Converte uma string para um enum `ConsumableType`.
     * @param typeStr A string que representa o tipo de consumível.
     * @return O enum `ConsumableType` correspondente à string.
     */
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

    /**
     * Encontra o maior número entre os salvamentos existentes.
     * @return O número do maior salvamento encontrado.
     */
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

    /**
     * Lê um arquivo de salvamento e converte seus dados em um objeto `Save`.
     * @param saveNumber O número do salvamento a ser lido.
     * @return Um objeto `Save` contendo os dados lidos do arquivo de salvamento.
     */
    Save read(int saveNumber) {
        string fileName = "../saves/save_" + to_string(saveNumber) + ".csv";

        ifstream file;
        file.open(fileName);

        Save loadedSave(PlayerInfo(0,0,0,0,0));

        string currentLine;
        while (!file.eof()) {
            getline(file, currentLine);

            vector<string> splittedString = splitString(currentLine, ',');
            string type = splittedString[0];

            if (type == "PLAYER_INFO") {
                // Lê informações do jogador
                int row, column, bombsAmount, specialbomb1, specialbomb2;

                row = toInt(splittedString[1]);
                column = toInt(splittedString[2]);
                bombsAmount = toInt(splittedString[3]);
                specialbomb1 = toInt(splittedString[4]);
                specialbomb2 = toInt(splittedString[5]);

                PlayerInfo loadedPlayerInfo(row, column, bombsAmount, specialbomb1, specialbomb2);
                loadedSave.playerInfo = loadedPlayerInfo;
            } else if (type == "ENEMY") {
                // Lê informações de um inimigo
                int row, column;

                row = toInt(splittedString[1]);
                column = toInt(splittedString[2]);

                SaveEnemy loadedEnemy(row, column);
                loadedSave.enemies.push_back(loadedEnemy);
            } else if (type == "CONSUMABLE") {
                // Lê informações de um consumível
                int row, column;

                row = toInt(splittedString[1]);
                column = toInt(splittedString[2]);
                ConsumableType consumableType = consumableTypeFromString(splittedString[3]);

                SaveConsumable loadedConsumable(row, column, consumableType);
                loadedSave.consumables.push_back(loadedConsumable);
            } else if (type == "BOMB") {
                // Lê informações de uma bomba
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
                // Lê informações gerais de salvamento
                loadedSave.saveName = splittedString[1];
                loadedSave.currentLevel = toInt(splittedString[2]);
                loadedSave.gameTime = toInt(splittedString[3]);
                loadedSave.placedBombs = toInt(splittedString[4]);
                loadedSave.enemiesAmount = toInt(splittedString[5]);
            }
            else if (type == "MAP") {
                // Lê informações do mapa
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

    vector<Save> readAllSavesInfo() {
        vector<Save> allSavesInfo;

        struct dirent *entry;
        DIR *dp = opendir("../saves");

        if (dp != nullptr) {
            while ((entry = readdir(dp))) {
                string filename = entry->d_name;
                if (filename.find("save_") == 0) {
                    string numberString = filename.substr(5, filename.length() - 9).c_str();

                    int saveNumber = toInt(numberString);

                    Save readedSave = read(saveNumber);
                    readedSave.saveNumber = saveNumber;

                    allSavesInfo.push_back(readedSave);
                }
            }
            closedir(dp);
        } else {
            cout << "Erro ao abrir a pasta de saves." << endl;
        }

        return allSavesInfo;
    }
}

#endif //GAME02_CBP_SAVEREADER_H
