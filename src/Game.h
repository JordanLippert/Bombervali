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
#include "entities/Player.h"
#include "utils/StringUtils.h"
#include "entities/Bombs.h"
#include "entities/Enemies.h"
#include "Menu.h"
#include "GameClock.h"
#include "utils/TimeFormat.h"

using namespace std;

namespace Game {
    bool running = true;
    COORD mouseCoord {};

    void tick() {
        int pressedKey;

        if (_kbhit()) {
            pressedKey = getch();
        }

        if (Menu::isPlayable()) {
            Player::tick(pressedKey);
            Bombs::tick();
            Enemies::tick();
            GameClock::tick();
        }

        Menu::tick(pressedKey);
    }
    
    // Camada de renderização do jogo
    void render() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mouseCoord);

        if (Menu::isPlayable()) {
            cout << "Tempo de jogo: " << TimeFormat::formatIntoString(GameClock::gameTime) << endl;
            for (int row = 0; row < MAP_HEIGHT; row++) {
                for (int column = 0; column < MAP_WIDTH; column++) {
                    // O método das bombas muda o fundo caso necessário e informa se deve escrever o símbolo da bomba no console
                    bool needToPrintBomb = Bombs::render(row, column);

                    // Verificar se o player está na posição atual, se sim, escrever o símbolo dele
                    if (Player::isInPosition(row, column)) {
                        cout << " " << Player::render() << " ";
                        ConsoleColor::reset();
                        continue;
                    }

                    // Verificar se um inimigo existe na posição atual, se sim, escrever o símbolo dos inimigos
                    if (Enemies::thereIsEnemy(row, column)) {
                        cout << " " << char(GameChar::ENEMY) << " ";
                        ConsoleColor::reset();
                        continue;
                    }

                    int tileType = MAP[row][column];

                    // Caso seja uma parede
                    if (tileType == 1) {
                        cout << char(GameChar::WALL) << char(GameChar::WALL) << char(GameChar::WALL);
                        ConsoleColor::reset();
                        continue;
                    }

                    // Caso seja uma parede frágil
                    if (tileType == 2) {
                        cout << char(GameChar::BREAKABLE_WALL) << char(GameChar::BREAKABLE_WALL) << char(GameChar::BREAKABLE_WALL);
                        ConsoleColor::reset();
                        continue;
                    }

                    // Por último se for um espaço vazio sem bomba, renderizar sem o símbolo
                    if (!needToPrintBomb) cout << "   ";
                    else std::cout << " " << char(GameChar::BOMB) << " ";

                    // Resetar a cor de fundo caso necessário
                    ConsoleColor::reset();
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

        // Inicializar os módulos do jogo
        Bombs::initBombsArray();
        Enemies::initEnemies();
    }
}

#endif //GAME02_GAME_H
