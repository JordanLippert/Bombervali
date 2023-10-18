//
// Created by caior on 17/10/2023.
//

#ifndef GAME02_CBP_HUD_H
#define GAME02_CBP_HUD_H

#include "utils/StringUtils.h"
#include "enums/GameChar.h"
#include "managers/MapManager.h"
#include "GameStatistics.h"
#include "utils/TimeFormat.h"

namespace Hud {
    int hudSize = 0;

    void renderDivider() {
        cout << endl << char(GameChar::HUD_LEFT_RIGHT);

        for (int i = 0; i < hudSize - 2; ++i) {
            cout << char(GameChar::HUD_HORIZONTAL);
        }

        cout << char(GameChar::HUD_RIGHT_LEFT);
    }

    void renderVerticalString(string display = "", string value = "") {
        cout << endl << char(GameChar::HUD_VERTICAL) << " ";

        cout << spaceAtRight(display + value, hudSize - 3);

        cout << char(GameChar::HUD_VERTICAL);
    }

    void renderBorder(char left, char right) {
        cout << left;
        for (int i = 0; i < hudSize - 2; ++i) {
            cout << char(GameChar::HUD_HORIZONTAL);
        }
        cout << right;
    }

    void render() {
        hudSize = MapManager::currentMap.getColumns() * 3;

        renderBorder(char(GameChar::HUD_TOP_LEFT), char(GameChar::HUD_TOP_RIGHT));
        renderVerticalString("Tempo de jogo: ", TimeFormat::formatIntoString(GameStatistics::gameTime));
        renderVerticalString("Bombas colocadas: ", to_string(GameStatistics::amountOfBombsPlaced) + ".");
        renderDivider();
        renderVerticalString("Inimigos restantes: ", to_string(Enemies::getAliveEnemiesAmount()) + ".");
        cout << endl;
        renderBorder(char(GameChar::HUD_BOTTOM_LEFT), char(GameChar::HUD_BOTTOM_RIGHT));
        cout << endl;
    }
}

#endif //GAME02_CBP_HUD_H
