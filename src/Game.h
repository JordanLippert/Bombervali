//
// Created by Caio on 25/08/2023.
//

#ifndef GAME02_GAME_H
#define GAME02_GAME_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include "../config.h"
#include "Player.h"
#include "utils/StringUtils.h"
#include "Bombs.h"
#include "Enemies.h"
#include "Menu.h"

using namespace std;

namespace Game {
    bool running = true;
    COORD mouseCoord {};

    // Camada de lógica do jogo
    void tick() {
        int pressedKey;

        if (_kbhit()) {
            pressedKey = getch();
        }

        if (Menu::isPlayable()) {
            Player::tick(pressedKey);
            Bombs::tick();
            Enemies::tick();
        }

        Menu::tick(pressedKey);
    }
    
    // Camada de renderização do jogo
    void render() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mouseCoord);

        if (Menu::isPlayable()) {
            for (int row = 0; row < MAP_HEIGHT; row++) {
                for (int column = 0; column < MAP_WIDTH; column++) {
                    bool needToPrintBomb = Bombs::render(row, column);

                    if (Player::isInPosition(row, column)) {
                        cout << " " << Player::render() << " ";
                        ConsoleColor::showColor(Color::RESET);
                        continue;
                    }

                    int tileType = MAP[row][column];

                    if (tileType == 1) {
                        cout << char(GameChar::WALL) << char(GameChar::WALL) << char(GameChar::WALL);
                        ConsoleColor::showColor(Color::RESET);
                        continue;
                    }

                    if (tileType == 2) {
                        cout << char(GameChar::BREAKABLE_WALL) << char(GameChar::BREAKABLE_WALL) << char(GameChar::BREAKABLE_WALL);
                        ConsoleColor::showColor(Color::RESET);
                        continue;
                    }

                    if (!needToPrintBomb) cout << "   ";
                    else std::cout << " " << char(GameChar::BOMB) << " ";

                    ConsoleColor::showColor(Color::RESET);
                }

                cout << endl;
            }

            return;
        }

        Menu::render();
    }

    // Método para começar a rodar o jogo, contendo o loop principal
    void run() {
        while (running) {
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

        Bombs::initBombsArray();
        Enemies::initEnemies();
    }
}

#endif //GAME02_GAME_H
