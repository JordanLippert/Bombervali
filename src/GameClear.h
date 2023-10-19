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
        PlayerLocation::reset = true;
        Enemies::enemies.clear();
        Bombs::bombs.clear();
        Consumables::consumables.clear();
        GameStatistics::gameTime = 0;
        GameStatistics::amountOfBombsPlaced = 0;
    }
}

#endif //GAME02_CBP_GAMECLEAR_H
