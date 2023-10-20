//
// Created by Caio on 27/08/2023.
//

#ifndef GAME02_STRINGUTILS_H
#define GAME02_STRINGUTILS_H

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> splitString(const string& text, char delimiter) {
    stringstream stream(text);
    string currentString;
    vector<string> list;

    while (getline(stream, currentString, delimiter)){
        list.push_back(currentString);
    }

    return list;
}

int toInt(const string& numberString) {
    int value = stoi(numberString);

    return value;
}

long toLong(const string& numberString) {
    long value = stol(numberString);

    return value;
}

bool contains(const std::string& str, char targetChar) {
    return str.find(targetChar) != std::string::npos;
}

string getNecessarySpacesToCenter(string str, int size) {
    int strLength = str.length();
    int spaces = (size - strLength) / 2;

    string newString;

    for (int i = 0; i < spaces; ++i) {
        newString += " ";
    }

    return newString;
}

string centerStringInScreen(string str, int size) {
    string newString = getNecessarySpacesToCenter(str, size);

    newString += str;

    return newString;
}

string spaceAtRight(string str, int size) {
    int strLength = str.length();
    int spaces = size - strLength;

    string newString;

    newString += str;

    for (int i = 0; i < spaces; ++i) {
        newString += " ";
    }

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
