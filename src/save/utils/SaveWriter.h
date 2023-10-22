//
// Created by Caio on 18/10/2023.
//

#ifndef GAME02_CBP_SAVEWRITER_H
#define GAME02_CBP_SAVEWRITER_H

#include <iostream>
#include <fstream>
#include "../../entities/Save.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace SaveWriter {
    /**
     * Converte um enum `ConsumableType` em uma string.
     * @param type O enum `ConsumableType` a ser convertido em string.
     * @return A representação em string do enum `ConsumableType`.
     */
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

    void deleteSave(int saveNumber) {
        string filename = "../saves/save_" + std::to_string(saveNumber) + ".csv";
        cout << filename;

        if (fs::exists(filename)) {
            try {
                fs::remove(filename);
                cout << "Save " << saveNumber << " deletado com sucesso." << std::endl;
            } catch (const std::exception& e) {
                cerr << "Erro ao deletar o save: " << e.what() << std::endl;
            }
        } else {
            cerr << "Save " << saveNumber << " não encontrado." << std::endl;
        }
    }

    /**
     * Escreve os dados de um objeto `Save` em um arquivo de salvamento.
     * @param save O objeto `Save` contendo os dados a serem escritos.
     * @param saveNumber O número do salvamento a ser gravado.
     */
    void write(Save& save, int saveNumber) {
        string fileName = "../saves/save_" + to_string(saveNumber) + ".csv";

        ofstream file;
        file.open(fileName, ios::out);

        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo." << endl;
            return;
        }

        // Escreve as informações do jogador
        file << "PLAYER_INFO," << save.playerInfo.row << "," << save.playerInfo.column << "," << save.playerInfo.bombsAmount << "," << save.playerInfo.specialbomb1 << "," << save.playerInfo.specialbomb2 << endl;

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

            file << "BOMB," << bomb.row << "," << bomb.column << "," << bomb.stage << "," << bomb.isFromPlayer << "," << bomb.ignoreWalls << "," << bomb.radius << endl;
        }

        // Escreve as informações gerais
        file << "SAVE_INFO," << save.saveName << "," << save.currentLevel << "," << save.gameTime << "," << save.placedBombs << "," << save.enemiesAmount << endl;

        // Escreve as informações do mapa
        file << "MAP," << save.map.getRows() << "," << save.map.getColumns() << endl;

        for (int i = 0; i < save.map.getTiles().size(); i++) {
            vector<int> row = save.map.getTiles()[i];

            for (int j = 0; j < save.map.getTiles()[i].size(); j++) {
                int tile = save.map.getTiles()[i][j];

                if (j + 1 == save.map.getTiles()[i].size()) {
                    file << tile;
                    continue;
                }
                file << tile << ",";
            }
            file << endl;
        }

        file.close();
    }
}

#endif //GAME02_CBP_SAVEWRITER_H
