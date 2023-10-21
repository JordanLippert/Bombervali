//
// Created by Caio on 27/08/2023.
//

#ifndef GAME02_STRINGUTILS_H
#define GAME02_STRINGUTILS_H

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Divide uma string em várias substrings com base em um delimitador.
 * @param text A string a ser dividida.
 * @param delimiter O caractere delimitador.
 * @return Um vetor de strings contendo as substrings resultantes.
 */
vector<string> splitString(const string& text, char delimiter) {
    stringstream stream(text);
    string currentString;
    vector<string> list;

    while (getline(stream, currentString, delimiter)){
        list.push_back(currentString);
    }

    return list;
}

/**
 * Converte uma string em um número inteiro.
 * @param numberString A string contendo o número a ser convertido.
 * @return O valor inteiro resultante da conversão.
 */
int toInt(const string& numberString) {
    int value = stoi(numberString);
    return value;
}

/**
 * Converte uma string em um número longo.
 * @param numberString A string contendo o número a ser convertido.
 * @return O valor longo resultante da conversão.
 */
long toLong(const string& numberString) {
    long value = stol(numberString);
    return value;
}

/**
 * Verifica se uma string contém um caractere específico.
 * @param str A string a ser verificada.
 * @param targetChar O caractere a ser procurado na string.
 * @return true se a string contém o caractere, false caso contrário.
 */
bool contains(const std::string& str, char targetChar) {
    return str.find(targetChar) != std::string::npos;
}

/**
 * Retorna uma string contendo espaços em branco para centralizar o texto.
 * @param str A string a ser centralizada.
 * @param size O tamanho total desejado.
 * @return A string com espaços em branco adicionados à esquerda para centralizar o texto.
 */
string getNecessarySpacesToCenter(string str, int size) {
    int strLength = str.length();
    int spaces = (size - strLength) / 2;
    string newString;

    for (int i = 0; i < spaces; ++i) {
        newString += " ";
    }

    return newString;
}

/**
 * Centraliza uma string no meio da tela com espaços em branco adicionados à esquerda.
 * @param str A string a ser centralizada.
 * @param size O tamanho total desejado.
 * @return A string centralizada no meio da tela.
 */
string centerStringInScreen(string str, int size) {
    string newString = getNecessarySpacesToCenter(str, size);
    newString += str;
    return newString;
}

/**
 * Adiciona espaços em branco à direita de uma string para atingir um tamanho específico.
 * @param str A string a ser formatada.
 * @param size O tamanho total desejado.
 * @return A string com espaços em branco adicionados à direita.
 */
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

/**
 * Substitui todas as ocorrências de uma substring em uma string por outra substring.
 * @param str A string na qual a substituição será feita.
 * @param from A substring a ser substituída.
 * @param to A substring que substituirá "from".
 */
void replaceString(string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == string::npos) return;

    str.replace(start_pos, from.length(), to);
}

/**
 * Cria uma barra de progresso formatada como uma string.
 * @param currentProgress O progresso atual.
 * @param maxProgress O progresso máximo.
 * @param barWidth A largura da barra de progresso.
 * @return A barra de progresso como uma string.
 */
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
