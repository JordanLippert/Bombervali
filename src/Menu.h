//
// Created by caior on 31/08/2023.
//

#ifndef GAME02_MENU_H
#define GAME02_MENU_H

#include <iostream>
#include "enums/GameStage.h"
#include "utils/StringUtils.h"
#include "entities/Enemies.h"
#include "map/GameMap.h"
#include "map/utils/MapReader.h"
#include "utils/Path.h"
#include "managers/MapManager.h"
#include "managers/GameStageManager.h"
#include "enums/MenuOptionType.h"
#include "MenuOptions.h"
#include "utils/TimeFormat.h"
#include "save/SaveSystem.h"

using namespace std;

namespace Menu {
    int terminalRows, terminalColumns;

    int selectedOption = 0;
    int maxOption = 3;
    MenuOptionType currentOptionType;

    // Função para renderizar as opções do menu
    void renderOptions(vector<MenuOptionType> options, Color focusColor = Color::LIGHT_BLUE) {
        maxOption = options.size() - 1;

        for (int i = 0; i < options.size(); ++i) {
            MenuOptionType current = options[i];

            string text;

            if (selectedOption == i) {
                text += char(175); // Define um símbolo especial para destacar a opção selecionada.
                text += " ";
                currentOptionType = current;
            }

            text += getTextFromType(current);

            cout << endl << endl << getNecessarySpacesToCenter(text, terminalColumns);

            if (selectedOption == i) {
                ConsoleColor::set(focusColor); // Define a cor do texto para a opção selecionada.
            } else {
                ConsoleColor::set(Color::WHITE); // Define a cor do texto para as outras opções.
            }

            cout << text;
            ConsoleColor::reset(); // Restaura a cor padrão do texto.
            cout << "       ";
        }
    }

    // Função para renderizar o menu de início do jogo
    void renderStartMenu() {
        cout << endl << endl;
        ConsoleColor::set(Color::LIGHT_BLUE);
        cout << centerStringInScreen(".______     ______   .___  ___. .______    _______ .______     ____    ____  ___       __       __ ", terminalColumns) << endl;
        cout << centerStringInScreen("|   _  \\   /  __  \\  |   \\/   | |   _  \\  |   ____||   _  \\    \\   \\  /   / /   \\     |  |     |  |", terminalColumns) << endl;
        cout << centerStringInScreen("|  |_)  | |  |  |  | |  \\  /  | |  |_)  | |  |__   |  |_)  |    \\   \\/   / /  ^  \\    |  |     |  |", terminalColumns) << endl;
        cout << centerStringInScreen("|   _  <  |  |  |  | |  |\\/|  | |   _  <  |   __|  |      /      \\      / /  /_\\  \\   |  |     |  |", terminalColumns) << endl;
        cout << centerStringInScreen("|  |_)  | |  `--'  | |  |  |  | |  |_)  | |  |____ |  |\\  \\----.  \\    / /  _____  \\  |  `----.|  |", terminalColumns) << endl;
        cout << centerStringInScreen("|______/   \\______/  |__|  |__| |______/  |_______|| _| `._____|   \\__/ /__/     \\__\\ |_______||__|", terminalColumns) << endl;
        ConsoleColor::set(Color::WHITE);
        cout << centerStringInScreen("v 2.0.0", terminalColumns);
        ConsoleColor::reset();
        cout << endl;

        renderOptions(MenuOptions::startMenu);
    }

    // Função para renderizar o menu de vitória
    void renderWin() {
        ConsoleColor::set(Color::GREEN);
        cout << endl << endl;
        cout << centerStringInScreen(" __   _____ _____ ___  ___ ___   _   ", terminalColumns) << endl;
        cout << centerStringInScreen(" \\ \\ / /_ _|_   _/ _ \\| _ \\_ _| /_\\  ", terminalColumns) << endl;
        cout << centerStringInScreen("  \\ V / | |  | || (_) |   /| | / _ \\ ", terminalColumns) << endl;
        cout << centerStringInScreen("   \\_/ |___| |_| \\___/|_|_\\___/_/ \\_\\", terminalColumns) << endl;
        ConsoleColor::reset();
        cout << endl;
        cout << centerStringInScreen("OBRIGADO POR JOGAR!", terminalColumns) << endl;
        cout << centerStringInScreen("Seu jogo durou: " + TimeFormat::formatIntoString(GameStatistics::gameTime), terminalColumns);

        renderOptions(MenuOptions::closeOrReturnMenu, Color::GREEN);
    }

    // Função para renderizar o menu de derrota
    void renderLose() {
        ConsoleColor::set(Color::RED);

        cout << endl << endl;
        cout << centerStringInScreen("  ___  ___ ___ ___  ___ _____ _   ", terminalColumns) << endl;
        cout << centerStringInScreen(" |   \\| __| _ \\ _ \\/ _ \\_   _/_\\  ", terminalColumns) << endl;
        cout << centerStringInScreen(" | |) | _||   /   / (_) || |/ _ \\ ", terminalColumns) << endl;
        cout << centerStringInScreen(" |___/|___|_|_\\_|_\\\\___/ |_/_/ \\_\\", terminalColumns) << endl;
        cout << endl;
        ConsoleColor::reset();
        cout << centerStringInScreen("OBRIGADO POR JOGAR!", terminalColumns) << endl;
        cout << centerStringInScreen("Seu jogo durou: " + TimeFormat::formatIntoString(GameStatistics::gameTime), terminalColumns);

        renderOptions(MenuOptions::closeOrReturnMenu, Color::RED);
    }

    // Função para renderizar os créditos do jogo
    void renderCredits() {
        ConsoleColor::set(Color::LIGHT_MAGENTA);
        cout << endl << endl;
        cout << centerStringInScreen("   ___ ___ ___ ___ ___ _____ ___  ___ ", terminalColumns) << endl;
        cout << centerStringInScreen("  / __| _ \\ __|   \\_ _|_   _/ _ \\/ __|", terminalColumns) << endl;
        cout << centerStringInScreen(" | (__|   / _|| |) | |  | || (_) \\__ \\", terminalColumns) << endl;
        cout << centerStringInScreen("  \\___|_|_\\___|___/___| |_| \\___/|___/", terminalColumns) << endl;
        cout << endl;
        ConsoleColor::set(Color::WHITE);
        cout << centerStringInScreen("Feito por: Caio Rosa, Guilherme Silvestre & Jordan Lippert", terminalColumns);
        cout << endl << endl;

        renderOptions(MenuOptions::closeOrReturnMenu, Color::LIGHT_MAGENTA);
    }

    // Função para renderizar o menu de avanço de fase
    void renderNextLevel() {
        ConsoleColor::set(Color::CYAN);
        cout << endl << endl;
        cout << centerStringInScreen("  _  _  _____   ___     ___ _   ___ ___ ", terminalColumns) << endl;
        cout << centerStringInScreen(" | \\| |/ _ \\ \\ / /_\\   | __/_\\ / __| __|", terminalColumns) << endl;
        cout << centerStringInScreen(" | .` | (_) \\ V / _ \\  | _/ _ \\\\__ \\ _| ", terminalColumns) << endl;
        cout << centerStringInScreen(" |_|\\_|\\___/ \\_/_/ \\_\\ |_/_/ \\_\\___/___|", terminalColumns) << endl;
        ConsoleColor::set(Color::WHITE);
        cout << endl << endl;
        cout << centerStringInScreen("Parabens! Voce matou todos os inimigos dessa fase.", terminalColumns) << endl;
        cout << centerStringInScreen("Aperte ENTER para continuar!", terminalColumns) << endl;
    }

    // Função para renderizar o menu de pausa
    void renderPauseMenu() {
        ConsoleColor::set(Color::CYAN);
        cout << endl << endl;
        cout << centerStringInScreen("  ___  _  _   _ ___ ___ ", terminalColumns) << endl;
        cout << centerStringInScreen(" | _ \\/_\\| | | / __| __|", terminalColumns) << endl;
        cout << centerStringInScreen(" |  _/ _ \\ |_| \\__ \\ _| ", terminalColumns) << endl;
        cout << centerStringInScreen(" |_|/_/ \\_\\___/|___/___|", terminalColumns) << endl;
        ConsoleColor::reset();
        cout << endl << endl;
        renderOptions(MenuOptions::pauseMenu, Color::CYAN);
    }

    // Função chamada para declarar derrota
    void loseGame() {
        GameStageManager::changeStage(GameStage::LOSE);
    }

    // Função para processar a lógica do menu com base nas teclas pressionadas
    void tick(int pressedKey) {
        // Verificar se está em um menu
        if (!GameStageManager::isPlayable()) {
            // Verificar se apertou ENTER
            if (pressedKey == 13) {
                if (GameStageManager::stage == GameStage::NEXT_LEVEL) {
                    GameStageManager::nextLevel();
                    GameStageManager::changeStage(GameStage::PLAYING);
                    return;
                }

                if (currentOptionType == MenuOptionType::NEW_GAME) {
                    GameStageManager::initNewGame();
                }
                if (currentOptionType == MenuOptionType::SAVE_GAME) {
                    string saveName = "Ola mundo";

                    SaveSystem::saveGame(saveName, 0);
                }
                if (currentOptionType == MenuOptionType::LOAD_GAME) {
                    SaveSystem::loadSave(0);
                    GameStageManager::changeStage(GameStage::PLAYING);
                }
                if (currentOptionType == MenuOptionType::RETURN_TO_START) {
                    selectedOption = 0;
                    GameStageManager::changeStage(GameStage::START);
                    GameStageManager::isGamePaused = false;
                }
                if (currentOptionType == MenuOptionType::RETURN_TO_GAME) {
                    selectedOption = 0;
                    GameStageManager::togglePause();
                }
                if (currentOptionType == MenuOptionType::CREDITS) {
                    selectedOption = 0;
                    GameStageManager::changeStage(GameStage::CREDITS);
                }
                if (currentOptionType == MenuOptionType::CLOSE_GAME) {
                    exit(0);
                }
            }

            // Sobe a opção no menu
            if ((pressedKey == 72 || pressedKey == 'w')) {
                selectedOption--;
                if (selectedOption < 0) selectedOption = maxOption;
            }

            // Desce a opção no menu
            if ((pressedKey == 80 || pressedKey == 's')) {
                selectedOption++;
                if (selectedOption > maxOption) selectedOption = 0;
            }
        }

        // Se está jogando, verifica se é para pausar o jogo
        if (pressedKey == 9 && GameStageManager::stage == GameStage::PLAYING) {
            GameStageManager::togglePause();
        }

        // Verifica a condição de vitória
        if (GameStageManager::stage == GameStage::PLAYING && Enemies::areAllEnemiesDead()) {
            if (MapManager::currentLevel == MapManager::MAX_LEVEL) {
                GameStageManager::changeStage(GameStage::WIN);
            } else {
                GameStageManager::changeStage(GameStage::NEXT_LEVEL);
            };
        }
    }

    /**
     * Método responsável pela camada de renderização dos menus
     */
    void render() {
        if (GameStageManager::stage == GameStage::START) {
            renderStartMenu();
        }

        if (GameStageManager::stage == GameStage::PLAYING && GameStageManager::isGamePaused) {
            renderPauseMenu();
        }

        if (GameStageManager::stage == GameStage::LOSE) {
            renderLose();
        }

        if (GameStageManager::stage == GameStage::WIN) {
            renderWin();
        }

        if (GameStageManager::stage == GameStage::NEXT_LEVEL) {
            renderNextLevel();
        }

        if (GameStageManager::stage == GameStage::CREDITS) {
            renderCredits();
        }
    }
}

#endif //GAME02_MENU_H
