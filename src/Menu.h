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
        cout << centerStringInScreen("  ___            _                      _ _ ", terminalColumns) << endl;
        cout << centerStringInScreen(" | _ ) ___ _ __ | |__  ___ _ ___ ____ _| (_)", terminalColumns) << endl;
        cout << centerStringInScreen(R"( | _ \/ _ \ '  \| '_ \/ -_) '_\ V / _` | | |)", terminalColumns) << endl;
        cout << centerStringInScreen(R"( |___/\___/_|_|_|_.__/\___|_|  \_/\__,_|_|_|)", terminalColumns) << endl;
        cout << centerStringInScreen("v 1.0.0", terminalColumns);

        cout << centerStringInScreen("\n\nPressione ENTER para iniciar o jogo.", terminalColumns);
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
