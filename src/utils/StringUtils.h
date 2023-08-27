//
// Created by Caio on 27/08/2023.
//

#ifndef GAME02_STRINGUTILS_H
#define GAME02_STRINGUTILS_H

#include <iostream>

using namespace std;

string placeSpaceInBorders(string str) {
    return " " + str + " ";
}

string placeSpaceInBorders(char str) {
    string returnString = " ";

    returnString += str;
    returnString += " ";

    return returnString;
}

#endif //GAME02_STRINGUTILS_H
