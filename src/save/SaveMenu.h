//
// Created by Caio on 21/10/2023.
//

#ifndef GAME02_CBP_SAVEMENU_H
#define GAME02_CBP_SAVEMENU_H

#include "../entities/Save.h"
#include "../utils/ConsoleColors.h"
#include "../enums/GameChar.h"
#include "../utils/StringUtils.h"
#include "SaveSystem.h"
#include "../managers/GameStageManager.h"

namespace SaveMenu {
    int terminalColumns;

    int selectedOption = 0;
    Save currentSave(PlayerInfo(0, 0, 0));
    const int HUD_SIZE = terminalColumns / 2;

    bool fetched = false;
    vector<Save> saves;

    void renderSaves() {
        if (saves.empty()) {
            cout << "Você ainda não tem nenhum save criado";
            return;
        }

        for (int i = 0; i < saves.size(); i++) {
            Save save = saves[i];
            bool isSelected = selectedOption == i;

            if (isSelected) {
                currentSave = save;
            }


        }
    }

    void renderLoadGameMenu() {
        ConsoleColor::set(Color::LIGHT_MAGENTA);

        cout << endl << endl;
        cout << centerStringInScreen("   ___   _   ___ ___ ___ ___   _   ___    ___   ___   _____ ", terminalColumns) << endl;
        cout << centerStringInScreen("  / __| /_\\ | _ \\ _ \\ __/ __| /_\\ | _ \\  / __| /_\\ \\ / / __|", terminalColumns) << endl;
        cout << centerStringInScreen(" | (__ / _ \\|   /   / _| (_ |/ _ \\|   /  \\__ \\/ _ \\ V /| _| ", terminalColumns) << endl;
        cout << centerStringInScreen("  \\___/_/ \\_\\_|_\\_|_\\___\\___/_/ \\_\\_|_\\  |___/_/ \\_\\_/ |___|", terminalColumns) << endl;
        cout << endl;
        ConsoleColor::reset();
    }

    void openLoadGameMenu() {
        fetched = false;
        GameStageManager::changeStage(GameStage::LOAD_GAME);
    }

    void tick() {
        if (!fetched) {
            saves = SaveSystem::getSavesInfos();
            fetched = true;
        }
    }

    void render(int columns) {
        terminalColumns = columns;
        if (GameStageManager::stage == GameStage::LOAD_GAME) {
            renderLoadGameMenu();
        }
    }
}



#endif //GAME02_CBP_SAVEMENU_H
