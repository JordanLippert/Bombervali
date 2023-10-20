//
// Created by Caio on 18/10/2023.
//

#ifndef GAME02_CBP_SAVESYSTEM_H
#define GAME02_CBP_SAVESYSTEM_H

#include <string>
#include "utils/SaveWriter.h"
#include "utils/SaveParser.h"

namespace SaveSystem {
    void saveGame(std::string& saveName) {
        Save save = SaveParser::createFromGame(saveName, CurrentPlayerInfo::row, CurrentPlayerInfo::column, CurrentPlayerInfo::bombsAmount);

        SaveWriter::write(save, 1);
    }
}

#endif //GAME02_CBP_SAVESYSTEM_H
