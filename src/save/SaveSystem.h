//
// Created by Caio on 18/10/2023.
//

#ifndef GAME02_CBP_SAVESYSTEM_H
#define GAME02_CBP_SAVESYSTEM_H

#include <string>
#include "utils/SaveWriter.h"
#include "utils/SaveParser.h"
#include "utils/SaveReader.h"
#include "utils/SaveLoader.h"

namespace SaveSystem {
    void saveGame(std::string& saveName, int saveNumber = -1) {
        Save save = SaveParser::createFromGame(saveName);
        if (saveNumber == -1) {
            saveNumber = SaveReader::findMajorSaveNumber() + 1;
        }

        SaveWriter::write(save, saveNumber);
    }

    void loadSave(int saveNumber) {
        Save save = SaveReader::read(saveNumber);

        SaveLoader::loadIntoGame(save);
    }
}

#endif //GAME02_CBP_SAVESYSTEM_H
