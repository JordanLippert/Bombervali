//
// Created by Caio on 18/10/2023.
//

#ifndef GAME02_CBP_SAVEWRITER_H
#define GAME02_CBP_SAVEWRITER_H

#include <iostream>
#include <fstream>
#include "../../entities/Save.h"

using namespace std;

namespace SaveWriter {
    string consumableTypeToString(ConsumableType type) {
        switch (type) {
            case ConsumableType::BOMB:
                return "BOMB";
            case ConsumableType::POWER_UP_DISTANCE:
                return "POWER_UP_DISTANCE";
            case ConsumableType::POWER_UP_IGNORE_WALLS:
                return "POWER_UP_IGNORE_WALLS";
            default:
                return "UNKNOWN";
        }
    }

    ConsumableType consumableTypeFromString(string& typeStr) {
        ConsumableType consumableType = ConsumableType::BOMB;

        if (typeStr == "POWER_UP_DISTANCE") {
            consumableType = ConsumableType::POWER_UP_DISTANCE;
        }
        else if (typeStr == "POWER_UP_IGNORE_WALLS") {
            consumableType = ConsumableType::POWER_UP_IGNORE_WALLS;
        }

        return consumableType;
    }

    void write(Save& save, int saveNumber) {
        string fileName = "../saves/save_" + to_string(saveNumber) + ".csv";

        ofstream file2(fileName);
        if (!file2.is_open()) {
            cout << "Erro ao criar o arquivo." << endl;
            return;
        }
        file2.close();

        ofstream file;
        file.open(fileName, ios::out);

        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo." << endl;
            return;
        }

        // Escreve as informações do jogador
        file << "PLAYER_INFO," << save.playerInfo.row << "," << save.playerInfo.column << "," << save.playerInfo.bombsAmount << endl;

        // Escreve as informações dos inimigos
        for (int i = 0; i < save.enemies.size(); i++) {
            SaveEnemy enemy = save.enemies[i];
            file << "ENEMY," << enemy.row << "," << enemy.column << endl;
        }

        // Escreve as informações dos itens consumíveis
        for (int i = 0; i < save.consumables.size(); i++) {
            SaveConsumable consumable = save.consumables[i];
            file << "CONSUMABLE," << consumable.row << "," << consumable.column << "," << consumableTypeToString(consumable.type) << endl;
        }

        // Escreve as informações das bombas
        for (int i = 0; i < save.bombs.size(); i++) {
            SaveBomb bomb = save.bombs[i];

            file << "BOMB," << bomb.row << "," << bomb.column << "," << bomb.stage << "," << bomb.isFromPlayer << "," << bomb.ignoreWalls << "," << bomb.radius << "," << bomb.placedAt << endl;
        }

        // Escreve as informações gerais
        file << "GENERAL_INFO," << save.saveName << "," << save.currentLevel << "," << save.gameTime << "," << save.placedBombs << "," << save.enemiesAmount << endl;

        file.close();
    }
}

#endif //GAME02_CBP_SAVEWRITER_H
