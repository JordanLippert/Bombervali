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

    for (int i = 0; i < spaces; ++i) {
        newString += " ";
    }

    return newString;
}

string placeSpaceInBorders(char str) {
    string returnString = " ";

    returnString += str;
    returnString += " ";

    return returnString;
}

#endif //GAME02_STRINGUTILS_H
