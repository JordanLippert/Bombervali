//
// Created by caior on 31/08/2023.
//

#ifndef GAME02_MENU_H
#define GAME02_MENU_H

#include <iostream>
#include "enums/GameStage.h"
#include "utils/StringUtils.h"

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
        cout << "Eu te analisei bastante, jogador. E eu já o meu veridito. NATURAL. Sim, eu acho que você é natural.";
    }

    void renderLose() {
        cout << "Infelizmente parece que você se explodiu :(";
    }

    void changeState(GameStage newStage) {
        stage = newStage;
        system("cls");
    }

    void tick(char pressedKey) {
        if (pressedKey == 13 && stage == GameStage::START) {
            changeState(GameStage::PLAYING);
        }
    }

    void render() {
        if (stage == GameStage::START) {
            renderStartMenu();
        }

        if (stage == GameStage::LOSE) {
            renderLose();
        }
    }
}

#endif //GAME02_MENU_H
