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
#include "../utils/HudUtils.h"

using namespace std;

namespace SaveMenu {
    int terminalColumns;

    int selectedOption = 0;
    Save selectedSave(PlayerInfo(0, 0, 0, 0, 0));
    int HUD_SIZE = 30;

    bool fetched = false;
    vector<Save> saves;

    void renderSaves(Color selectedColor = Color::LIGHT_MAGENTA) {
        bool existSaves = !saves.empty();
        if (!existSaves) {
            ConsoleColor::set(Color::WHITE);
            cout << centerStringInScreen("Voce ainda nao salvou um jogo", terminalColumns) << endl << endl;
            ConsoleColor::reset();
        }

        for (int i = 0; i < saves.size(); i++) {
            Save save = saves[i];
            bool isSelected = selectedOption == i;

            if (isSelected) {
                selectedSave = save;
            }

            string saveNameText = "#" + to_string(save.saveNumber) + " " + save.saveName;
            string levelString = "Fase: " + to_string(save.currentLevel);
            string playedTimeText = TimeFormat::formatIntoString(save.gameTime, true) + " jogados";
            string remainingEnemiesText = to_string(save.enemiesAmount) + " inimigos";

            string spacesToCenter = generateSpaces((terminalColumns - HUD_SIZE) / 2);

            Color hudColor = isSelected ? selectedColor : Color::LIGHTGRAY;

            cout << spacesToCenter;
            HudUtils::renderTopBorder(HUD_SIZE, hudColor);
            HudUtils::renderTwoStrings(saveNameText, levelString, HUD_SIZE, spacesToCenter, hudColor);
            HudUtils::renderTwoStrings(playedTimeText, remainingEnemiesText, HUD_SIZE, spacesToCenter, hudColor);
            cout << endl << spacesToCenter;
            HudUtils::renderBottomBorder(HUD_SIZE, hudColor);
            cout << endl;
        }

        int isSaveGame = GameStageManager::stage == GameStage::LOAD_GAME ? 0 : 1;

        if (isSaveGame) {
            string saveText;
            ConsoleColor::set(Color::WHITE);
            if (selectedOption == (saves.size())) {
                ConsoleColor::set(Color::LIGHT_BLUE);
                saveText += char(175);
                saveText += " ";
            }
            saveText += "Criar novo save";

            cout << centerStringInScreen(saveText, terminalColumns) << endl << endl;
        }

        string exitText;
        ConsoleColor::set(Color::WHITE);
        if (selectedOption == (saves.size() + isSaveGame)) {
            ConsoleColor::set(isSaveGame ? Color::LIGHT_BLUE : Color::LIGHT_MAGENTA);
            exitText += char(175);
            exitText += " ";
        }
        exitText += "Voltar ao menu";

        cout << centerStringInScreen(exitText, terminalColumns) << endl;
    }

    void renderSaveGameMenu() {
        ConsoleColor::set(Color::LIGHT_BLUE);

        cout << endl << endl;
        cout << centerStringInScreen("  ___   _   _ __   ___   ___       _  ___   ___  ___  ", terminalColumns) << endl;
        cout << centerStringInScreen(" / __| /_\\ | |\\ \\ / /_\\ | _ \\   _ | |/ _ \\ / __|/ _ \\ ", terminalColumns) << endl;
        cout << centerStringInScreen(" \\__ \\/ _ \\| |_\\ V / _ \\|   /  | || | (_) | (_ | (_) |", terminalColumns) << endl;
        cout << centerStringInScreen(" |___/_/ \\_\\____\\_/_/ \\_\\_|_\\   \\__/ \\___/ \\___|\\___/ ", terminalColumns) << endl;
        cout << endl;
        renderSaves(Color::LIGHT_BLUE);
        ConsoleColor::reset();
        if (!saves.empty()) {
            cout << endl;
            cout << centerStringInScreen("Aperte ENTER em um salvamento para sobrescrever", terminalColumns) << endl;
            cout << centerStringInScreen("Aperte DELETE para deletar um salvamento", terminalColumns) << endl;
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
        renderSaves();
        ConsoleColor::reset();
        if (!saves.empty()) {
            cout << endl;
            cout << centerStringInScreen("Aperte ENTER para carregar o save", terminalColumns) << endl;
            cout << centerStringInScreen("Aperte DELETE para deletar o save", terminalColumns) << endl;
        }
    }

    void openLoadGameMenu() {
        fetched = false;
        GameStageManager::changeStage(GameStage::LOAD_GAME);
        selectedOption = 0;
    }

    void openSaveGameMenu() {
        fetched = false;
        GameStageManager::changeStage(GameStage::SAVE_GAME);
        selectedOption = 0;
    }

    void tick(int pressedKey) {
        if (!fetched) {
            system("cls");
            saves = SaveSystem::getSavesInfos();
            fetched = true;
        }

        if (pressedKey == 13) {
            if (GameStageManager::stage == GameStage::LOAD_GAME) {
                if (selectedOption == saves.size()) {
                    GameStageManager::changeStage(GameStage::START);
                    return;
                }

                if (!saves.empty()) {
                    SaveSystem::loadSave(selectedSave.saveNumber);
                    GameStageManager::changeStage(GameStage::PLAYING);
                    return;
                }
            }
            if (GameStageManager::stage == GameStage::SAVE_GAME) {
                if (selectedOption == saves.size()) {
                    fflush(stdin);
                    ConsoleColor::set(Color::WHITE);
                    cout << endl << centerStringInScreen("Insira o nome do salvamento: ", terminalColumns, false);
                    string saveName;

                    ConsoleColor::set(Color::LIGHT_BLUE);
                    std::getline(std::cin, saveName);

                    SaveSystem::saveGame(saveName);
                    fetched = false;
                    return;
                }

                if (selectedOption == saves.size() + 1) {
                    GameStageManager::changeStage(GameStage::PLAYING);
                    return;
                }

                if (!saves.empty()) {
                    SaveSystem::saveGame(selectedSave.saveName, selectedSave.saveNumber);
                    fetched = false;
                    system("cls");
                }
            }
        }

        // Verificar se apertou DELETE ou BACKSPACE
        if (pressedKey == 46 || pressedKey == 8) {
            if (!saves.empty() && selectedOption < saves.size()) {
                ConsoleColor::set(Color::RED);
                SaveSystem::deleteSave(selectedSave.saveNumber);
                system("cls");
                fetched = false;
                return;
            }
        }

        int isSaveGame = GameStageManager::stage == GameStage::LOAD_GAME ? 0 : 1;

        // Sobe a opção no menu
        if ((pressedKey == 72 || pressedKey == 'w')) {
            selectedOption--;
            if (selectedOption < 0) selectedOption = (saves.empty() ? 1 : saves.size() + 1);
        }

        // Desce a opção no menu
        if ((pressedKey == 80 || pressedKey == 's')) {
            selectedOption++;
            if (selectedOption > saves.size() + isSaveGame) selectedOption = 0;
        }
    }

    void render(int columns) {
        terminalColumns = columns;
        HUD_SIZE = terminalColumns / 2;
        if (GameStageManager::stage == GameStage::LOAD_GAME) {
            renderLoadGameMenu();
        }
        if (GameStageManager::stage == GameStage::SAVE_GAME) {
            renderSaveGameMenu();
        }
    }
}



#endif //GAME02_CBP_SAVEMENU_H
