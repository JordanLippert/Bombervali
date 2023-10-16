//
// Created by Caio on 27/08/2023.
//

#ifndef GAME02_STRINGUTILS_H
#define GAME02_STRINGUTILS_H

#include <iostream>

using namespace std;

string centerStringInScreen(string str, int size) {
    int strLength = str.length();
    int spaces = (size - strLength) / 2;

    string newString;

    for (int i = 0; i < spaces; ++i) {
        newString += " ";
    }

    newString += str;

    return newString;
}

void replaceString(string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == string::npos)
        return;
    str.replace(start_pos, from.length(), to);
}

string getProgressBar(int currentProgress, int maxProgress, int barWidth) {
    int percent = (currentProgress * 100) / maxProgress;

    int numChars = (barWidth * percent) / 100;
    string bar;

    bar.append("[");
    for (int i = 0; i < barWidth; i++) {
        if (i < numChars) {
            bar.append("#");
        } else {
            bar.append(" ");
        }
    }

    bar.append("] ");

    return bar;
}

#endif //GAME02_STRINGUTILS_H
