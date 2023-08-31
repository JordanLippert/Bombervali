//
// Created by caior on 31/08/2023.
//

#ifndef GAME02_MENU_H
#define GAME02_MENU_H

#include <iostream>
#include "enums/GameStage.h"

using namespace std;

namespace Menu {
    GameStage stage = GameStage::START;

    bool isPlayable() {
        return stage == GameStage::PLAYING;
    }

    void renderStartMenu() {
        cout << "Opa meu chapa, aperta ENTER pra começar vai.";
    }

    void renderWin() {
        cout << "Eu te analisei bastante, jogador. E eu já o meu veridito. NATURAL. Sim, eu acho que você é natural.";
    }

    void renderLose() {
        cout << "Se fudeu otário, tomou bimba na bundinha. Quem você acha que é? C bam? Chris Bumbstead? Eu acho que não é mesmo. FAKE NATTY!";
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
    }
}

#endif //GAME02_MENU_H
