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

using namespace std;

namespace Menu {
    int terminalRows, terminalColumns;

    int selectedOption = 0;
    int maxOption = 3;

    /**
     * Escrever o managers de inicio do jogo no console
     */
    void renderStartMenu() {
        cout << endl << endl;
        cout << centerStringInScreen(".______     ______   .___  ___. .______    _______ .______     ____    ____  ___       __       __ ", terminalColumns) << endl;
        cout << centerStringInScreen("|   _  \\   /  __  \\  |   \\/   | |   _  \\  |   ____||   _  \\    \\   \\  /   / /   \\     |  |     |  |", terminalColumns) << endl;
        cout << centerStringInScreen("|  |_)  | |  |  |  | |  \\  /  | |  |_)  | |  |__   |  |_)  |    \\   \\/   / /  ^  \\    |  |     |  |", terminalColumns) << endl;
        cout << centerStringInScreen("|   _  <  |  |  |  | |  |\\/|  | |   _  <  |   __|  |      /      \\      / /  /_\\  \\   |  |     |  |", terminalColumns) << endl;
        cout << centerStringInScreen("|  |_)  | |  `--'  | |  |  |  | |  |_)  | |  |____ |  |\\  \\----.  \\    / /  _____  \\  |  `----.|  |", terminalColumns) << endl;
        cout << centerStringInScreen("|______/   \\______/  |__|  |__| |______/  |_______|| _| `._____|   \\__/ /__/     \\__\\ |_______||__|", terminalColumns) << endl;
        cout << centerStringInScreen("v 1.0.0", terminalColumns);
        cout << endl;
        cout << centerStringInScreen("Caio Rosa, Guilherme Silvestre & Jordan Lippert @ Univali", terminalColumns);

        cout << endl << endl << centerStringInScreen("Pressione ENTER para iniciar o jogo.", terminalColumns);
    }

    /**
     * Escrever o managers de vitória do jogo no console
     */
    void renderWin() {
        ConsoleColor::set(Color::GREEN);
        cout << endl << endl;
        cout << centerStringInScreen(" __   _____ _____ ___  ___ ___   _   ", terminalColumns) << endl;
        cout << centerStringInScreen(" \\ \\ / /_ _|_   _/ _ \\| _ \\_ _| /_\\  ", terminalColumns) << endl;
        cout << centerStringInScreen("  \\ V / | |  | || (_) |   /| | / _ \\ ", terminalColumns) << endl;
        cout << centerStringInScreen("   \\_/ |___| |_| \\___/|_|_\\___/_/ \\_\\", terminalColumns) << endl;
        ConsoleColor::reset();
        cout << endl;
        cout << centerStringInScreen("OBRIGADO POR JOGAR!", terminalColumns);
        cout << endl;
        cout << centerStringInScreen("Feito por: Caio Rosa, Guilherme Silvestre & Jordan Lippert", terminalColumns);
    }

    /**
     * Escrever o managers de derrota do jogo no console
     */
    void renderLose() {
        ConsoleColor::set(Color::RED);

        cout << endl << endl;
        cout << centerStringInScreen("  ___  ___ ___ ___  ___ _____ _   ", terminalColumns) << endl;
        cout << centerStringInScreen(" |   \\| __| _ \\ _ \\/ _ \\_   _/_\\  ", terminalColumns) << endl;
        cout << centerStringInScreen(" | |) | _||   /   / (_) || |/ _ \\ ", terminalColumns) << endl;
        cout << centerStringInScreen(" |___/|___|_|_\\_|_\\\\___/ |_/_/ \\_\\", terminalColumns) << endl;
        cout << endl;
        ConsoleColor::reset();
        cout << centerStringInScreen("OBRIGADO POR JOGAR!", terminalColumns);
        cout << endl;
        cout << centerStringInScreen("Feito por: Caio Rosa, Guilherme Silvestre & Jordan Lippert", terminalColumns);
    }

    /**
     * Escrever o managers de vitória do jogo no console
     */
    void renderPauseMenu() {
        ConsoleColor::set(Color::CYAN);
        cout << endl << endl;
        cout << centerStringInScreen("  ___  _  _   _ ___ ___ ", terminalColumns) << endl;
        cout << centerStringInScreen(" | _ \\/_\\| | | / __| __|", terminalColumns) << endl;
        cout << centerStringInScreen(" |  _/ _ \\ |_| \\__ \\ _| ", terminalColumns) << endl;
        cout << centerStringInScreen(" |_|/_/ \\_\\___/|___/___|", terminalColumns) << endl;
        ConsoleColor::reset();
        cout << endl;
        cout << centerStringInScreen("Aperte TAB para voltar a jogar.", terminalColumns);
        cout << endl;
    }

    void loseGame() {
        GameStageManager::changeStage(GameStage::LOSE);
    }

    /**
     * Método responsável pela lógica dos menus
     * @param pressedKey
     */
    void tick(int pressedKey) {
        // Se está no estágio de início, verifica se apertou ENTER para iniciar
        if (pressedKey == 13 && GameStageManager::stage == GameStage::START) {
            GameStageManager::initNewGame();
        }

        // Se está jogando, verifica se é para pausar o jogo
        if (pressedKey == 9 && GameStageManager::stage == GameStage::PLAYING) {
            GameStageManager::togglePause();
        }

        // Verifica a condição de vitória
        if (GameStageManager::stage == GameStage::PLAYING && Enemies::areAllEnemiesDead()) {
            GameStageManager::changeStage(GameStage::WIN);
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
    }
}

#endif //GAME02_MENU_H
