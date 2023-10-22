//
// Created by Caio on 21/10/2023.
//

#ifndef GAME02_CBP_HUDUTILS_H
#define GAME02_CBP_HUDUTILS_H

#include "ConsoleColors.h"
#include "../enums/GameChar.h"
#include "StringUtils.h"

using namespace std;

namespace HudUtils {
    // Função para renderizar a linha de separação no HUD
    void renderDivider(int hudSize) {
        ConsoleColor::set(Color::LIGHTGRAY);
        cout << endl << char(GameChar::HUD_LEFT_RIGHT);

        for (int i = 0; i < hudSize - 2; ++i) {
            cout << char(GameChar::HUD_HORIZONTAL);
        }

        cout << char(GameChar::HUD_RIGHT_LEFT);
    }

    // Função para renderizar dois textos na HUD
    void renderTwoStrings(const string& text, const string& text2, int hudSize) {
        cout << endl << char(GameChar::HUD_VERTICAL) << " ";

        ConsoleColor::set(Color::WHITE);
        cout << text;
        cout << getNecessarySpacesToDivideTexts(text, text2, hudSize - 3);
        cout << text2;
        ConsoleColor::set(Color::LIGHTGRAY);

        cout << char(GameChar::HUD_VERTICAL);
    }

    // Função para renderizar uma linha vertical de texto no HUD
    void renderVerticalString(string display = "", string value = "", int hudSize = 0) {
        cout << endl << char(GameChar::HUD_VERTICAL) << " ";

        ConsoleColor::set(Color::WHITE);
        cout << spaceAtRight(display + value, hudSize - 3);
        ConsoleColor::set(Color::LIGHTGRAY);

        cout << char(GameChar::HUD_VERTICAL);
    }

    // Função para renderizar uma linha de texto centralizada no HUD
    void renderCenterString(string text, int hudSize) {
        cout << endl << char(GameChar::HUD_VERTICAL) << " ";

        cout << getNecessarySpacesToCenter(text, hudSize - 3);
        ConsoleColor::set(Color::LIGHT_BLUE);
        cout << text;
        ConsoleColor::set(Color::LIGHTGRAY);
        cout << getNecessarySpacesToCenter(text, hudSize - 3);

        cout << char(GameChar::HUD_VERTICAL);
    }

    // Função para renderizar a borda superior ou inferior do HUD
    void renderBorder(char left, char right, int hudSize) {
        cout << left;
        for (int i = 0; i < hudSize - 2; ++i) {
            cout << char(GameChar::HUD_HORIZONTAL);
        }
        cout << right;
    }
}

#endif //GAME02_CBP_HUDUTILS_H
