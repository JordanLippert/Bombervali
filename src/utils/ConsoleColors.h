//
// Created by Caio on 25/08/2023.
//

#ifndef GAME02_CONSOLECOLORS_H
#define GAME02_CONSOLECOLORS_H

#include <iostream>
#include <windows.h>

enum class Color {
    RESET = 15,
    RED = 12,
    GREEN = 10,
    RED_BACKGROUND = 207,
    ORANGE_BACKGROUND = 111,
    YELLOW_BACKGROUND = 239,
    WHITE_BACKGROUND = 240,
};

namespace ConsoleColor {
    void showColor(Color color) {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(console, int(color));
    }
}

#endif //GAME02_CONSOLECOLORS_H
