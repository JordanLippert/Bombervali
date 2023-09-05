//
// Created by caior on 31/08/2023.
//

#ifndef GAME02_MENU_H
#define GAME02_MENU_H

#include <iostream>
#include "enums/GameStage.h"
#include "utils/StringUtils.h"
#include "Enemies.h"

using namespace std;

namespace Menu {
    GameStage stage = GameStage::START;
    int terminalRows, terminalColumns;

    bool isPlayable() {
        return stage == GameStage::PLAYING;
    }

    void renderStartMenu() {
        cout << endl << endl;
        cout << centerStringInScreen("  ___  ___  __  __ ___ ___ _____   ___   _    ___ ", terminalColumns) << endl;
        cout << centerStringInScreen(" | _ )/ _ \\|  \\/  | _ ) __| _ \\ \\ / /_\\ | |  |_ _|", terminalColumns) << endl;
        cout << centerStringInScreen(" | _ \\ (_) | |\\/| | _ \\ _||   /\\ V / _ \\| |__ | | ", terminalColumns) << endl;
        cout << centerStringInScreen(" |___/\\___/|_|  |_|___/___|_|_\\ \\_/_/ \\_\\____|___|", terminalColumns) << endl;
        cout << centerStringInScreen("v 1.0.0", terminalColumns);
        cout << endl;
        cout << centerStringInScreen("Caio Rosa, Guilherme Silvestre & Jordan Lippert @ Univali", terminalColumns);

        cout << endl << endl << centerStringInScreen("Pressione ENTER para iniciar o jogo.", terminalColumns);
    }

    void renderWin() {
        ConsoleColor::showColor(Color::GREEN);
        cout << endl << endl;
        cout << centerStringInScreen(" __   _____ _____ ___  ___ ___   _   ", terminalColumns) << endl;
        cout << centerStringInScreen(" \\ \\ / /_ _|_   _/ _ \\| _ \\_ _| /_\\  ", terminalColumns) << endl;
        cout << centerStringInScreen("  \\ V / | |  | || (_) |   /| | / _ \\ ", terminalColumns) << endl;
        cout << centerStringInScreen("   \\_/ |___| |_| \\___/|_|_\\___/_/ \\_\\", terminalColumns) << endl;
        ConsoleColor::showColor(Color::RESET);
        cout << endl;
        cout << centerStringInScreen("OBRIGADO POR JOGAR!", terminalColumns);
        cout << endl;
        cout << centerStringInScreen("Feito por: Caio Rosa, Guilherme Silvestre & Jordan Lippert", terminalColumns);
    }

    void renderLose() {
        ConsoleColor::showColor(Color::RED);

        cout << endl << endl;
        cout << centerStringInScreen("  ___  ___ ___ ___  ___ _____ _   ", terminalColumns) << endl;
        cout << centerStringInScreen(" |   \\| __| _ \\ _ \\/ _ \\_   _/_\\  ", terminalColumns) << endl;
        cout << centerStringInScreen(" | |) | _||   /   / (_) || |/ _ \\ ", terminalColumns) << endl;
        cout << centerStringInScreen(" |___/|___|_|_\\_|_\\\\___/ |_/_/ \\_\\", terminalColumns) << endl;
        cout << endl;
        ConsoleColor::showColor(Color::RESET);
        cout << centerStringInScreen("OBRIGADO POR JOGAR!", terminalColumns);
        cout << endl;
        cout << centerStringInScreen("Feito por: Caio Rosa, Guilherme Silvestre & Jordan Lippert", terminalColumns);
    }

    void changeState(GameStage newStage) {
        stage = newStage;
        system("cls");
    }

    void tick(char pressedKey) {
        if (pressedKey == 13 && stage == GameStage::START) {
            changeState(GameStage::PLAYING);
        }

        if (stage == GameStage::PLAYING && Enemies::areAllEnemiesDead()) {
            changeState(GameStage::WIN);
        }
    }

    void render() {
        if (stage == GameStage::START) {
            renderStartMenu();
        }

        if (stage == GameStage::LOSE) {
            renderLose();
        }

        if (stage == GameStage::WIN) {
            renderWin();
        }
    }
}

#endif //GAME02_MENU_H
