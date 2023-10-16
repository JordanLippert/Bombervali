//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_MAPREADER_H
#define GAME02_CBP_MAPREADER_H

#include <fstream>
#include "../GameMap.h"
#include "../../utils/StringUtils.h"

namespace MapReader {
    GameMap readFromFile(const string& fileName) {
        ifstream file;

        int rows = 0, columns = 0;
        vector<vector<int>> loadedTiles;

        file.open(fileName);

        string currentLine;
        while (!file.eof()) {
            getline(file, currentLine);

            if (contains(currentLine, '=')) {
                vector<string> splittedString = splitString(currentLine, '=');

                if (splittedString[0] == "HEIGHT") {
                    rows = toInt(splittedString[1]);
                }

                if (splittedString[0] == "WIDTH") {
                    columns = toInt(splittedString[1]);
                }
                continue;
            }

            if (rows == 0 || columns == 0) {
                continue;
            }

            vector<string> splittedString = splitString(currentLine, ',');

            vector<int> columnVector;

            for (int i = 0; i < splittedString.size(); ++i) {
                string stringValue = splittedString[i];

                int intValue = toInt(stringValue);

                columnVector.push_back(intValue);
            }

            loadedTiles.push_back(columnVector);
        }

        GameMap newMap(rows, columns, loadedTiles);

        return newMap;
    }
}

#endif //GAME02_CBP_MAPREADER_H
