//
// Created by Caio on 19/10/2023.
//

#ifndef GAME02_CBP_SAVEPARSER_H
#define GAME02_CBP_SAVEPARSER_H

#include <utility>

#include "../../entities/Save.h"
#include "../../GameStatistics.h"
#include "../../entities/Enemies.h"
#include "../../entities/Consumables.h"
#include "../../entities/Bombs.h"

namespace SaveParser {
    /**
     * Cria um objeto de salvamento a partir do estado atual do jogo.
     * @param saveName O nome do salvamento.
     * @return Retorna um objeto de salvamento contendo os dados do jogo a serem salvos.
     */
    Save createFromGame(string saveName) {
        // Obter informações do jogador atual
        int playerRow = CurrentPlayerInfo::row;
        int playerColumn = CurrentPlayerInfo::column;
        int bombsAmountOfPlayer = CurrentPlayerInfo::bombsAmount;

        // Inicializar o objeto de salvamento com as informações do jogador
        Save save(PlayerInfo(playerRow, playerColumn, bombsAmountOfPlayer));

        // Copiar estatísticas do jogo e outras informações relevantes
        save.placedBombs = GameStatistics::amountOfBombsPlaced;
        save.gameTime = GameStatistics::gameTime;
        save.enemiesAmount = Enemies::enemies.getSize();
        save.currentLevel = MapManager::currentLevel;
        save.map = MapManager::currentMap;
        save.saveName = std::move(saveName);

        // Copiar informações sobre os inimigos no jogo
        for (int i = 0; i < Enemies::enemies.getSize(); ++i) {
            Enemy currentEnemy = Enemies::enemies[i];

            SaveEnemy newSaveEnemy(currentEnemy.row, currentEnemy.column);

            save.enemies.push_back(newSaveEnemy);
        }

        // Copiar informações sobre os consumíveis no jogo
        for (int i = 0; i < Consumables::consumables.getSize(); ++i) {
            Consumable current = Consumables::consumables[i];

            SaveConsumable newSaveConsumable(current.row, current.column, current.type);

            save.consumables.push_back(newSaveConsumable);
        }

        // Copiar informações sobre as bombas no jogo
        for (int i = 0; i < Bombs::bombs.getSize(); ++i) {
            Bomb current = Bombs::bombs[i];

            SaveBomb newSaveBomb(current.row, current.column, current.stage, current.isFromPlayer, current.ignoreWalls, current.radius);

            save.bombs.push_back(newSaveBomb);
        }

        return save;
    }
}

#endif //GAME02_CBP_SAVEPARSER_H
