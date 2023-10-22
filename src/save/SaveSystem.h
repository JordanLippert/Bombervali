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
    /**
     * Salva o estado atual do jogo com um nome de salvamento específico.
     * @param saveName O nome do arquivo de salvamento.
     * @param saveNumber O número de salvamento (opcional). Se não fornecido, será calculado automaticamente.
     */
    void saveGame(std::string& saveName, int saveNumber = -1) {
        Save save = SaveParser::createFromGame(saveName);
        if (saveNumber == -1) {
            saveNumber = SaveReader::findMajorSaveNumber() + 1;
        }

        SaveWriter::write(save, saveNumber);
    }

    /**
     * Salva o estado atual do jogo com um nome de salvamento específico.
     * @param saveName O nome do arquivo de salvamento.
     * @param saveNumber O número de salvamento (opcional). Se não fornecido, será calculado automaticamente.
     */
    vector<Save> getSavesInfos() {
        return SaveReader::readAllSavesInfo();
    }

    void deleteSave(int saveNumber) {
        SaveWriter::deleteSave(saveNumber);
    }

    /**
     * Carrega um estado de salvamento específico no jogo.
     * @param saveNumber O número de salvamento a ser carregado.
     */
    void loadSave(int saveNumber) {
        Save save = SaveReader::read(saveNumber);

        SaveLoader::loadIntoGame(save);
    }
}

#endif //GAME02_CBP_SAVESYSTEM_H
