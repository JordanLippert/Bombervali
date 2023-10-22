//
// Created by Caio on 19/10/2023.
//

#ifndef GAME02_CBP_GAMECLEAR_H
#define GAME02_CBP_GAMECLEAR_H

#include "map/PlayerLocation.h"
#include "entities/Enemies.h"
#include "entities/Bombs.h"
#include "entities/Consumables.h"

namespace GameClear {
    void clean() {
        // Define que o jogador deve ser reposicionado na próxima partida
        PlayerLocation::reset = true;
        PlayerLocation::specialbomb2 = 0;
        PlayerLocation::specialbomb1 = 0;
        // Limpa a lista de inimigos
        Enemies::enemies.clear();
        // Limpa a lista de bombas
        Bombs::bombs.clear();
        // Limpa a lista de itens consumíveis
        Consumables::consumables.clear();
        // Reinicia o tempo de jogo
        GameStatistics::gameTime = 0;
        // Reinicia a contagem de bombas colocadas
        GameStatistics::amountOfBombsPlaced = 0;
    }
}

#endif //GAME02_CBP_GAMECLEAR_H
