//
// Created by Caio on 25/08/2023.
//

#ifndef GAME02_GAME_H
#define GAME02_GAME_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include "entities/Player.h"
#include "utils/StringUtils.h"
#include "entities/Bombs.h"
#include "entities/Enemies.h"
#include "Menu.h"
#include "GameStatistics.h"
#include "map/utils/MapRender.h"
#include "managers/MapManager.h"
#include "Hud.h"
#include "MenuOptions.h"

using namespace std;

namespace Game {
    bool running = true;
    COORD mouseCoord {};

    void tick() {
        int pressedKey;

        if (_kbhit()) {
            pressedKey = getch();
        }

        if (GameStageManager::isPlayable()) {
            if (PlayerLocation::reset) {
                PlayerLocation::reset = false;
                Player::row = PlayerLocation::row;
                Player::column = PlayerLocation::column;
                Player::bombsAmount = 5;
            }

            Player::tick(pressedKey);
            Bombs::tick();
            Enemies::tick();
            GameStatistics::tick();
        }

        Menu::tick(pressedKey);
    }

    // Camada de renderização do jogo
    void render() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mouseCoord);

        if (GameStageManager::isPlayable()) {
            Hud::render();
            MapRender::render(MapManager::currentMap);
            return;
        }

        Menu::render();
    }

    // Método para começar a rodar o jogo, contendo o loop principal
    void run() {
        while (running) {
            // Primeiro a camada de lógica, e depois a renderização do Mapa / Menu
            tick();
            render();
        }
    }

    // Método que deve ser chamado antes de rodar o jogo
    void initializeGame() {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);
        Menu::terminalColumns = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
        Menu::terminalRows = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;

        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);

        mouseCoord.X = 0;
        mouseCoord.Y = 0;
        srand(time(NULL));

        MenuOptions::init();
    }
}

#endif //GAME02_GAME_H
