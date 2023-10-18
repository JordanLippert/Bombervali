//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_GAMESTAGEMANAGER_H
#define GAME02_CBP_GAMESTAGEMANAGER_H

#include "MapManager.h"
#include "../enums/GameStage.h"
#include "../map/utils/MapLoader.h"
#include <iostream>

namespace GameStageManager {
    GameStage stage = GameStage::START;
    bool isGamePaused = false;

    /**
     * Este método retorna se o estágio do jogo é jogável
     */
    bool isPlayable() {
        return stage == GameStage::PLAYING && !isGamePaused;
    }

    /**
    * Este metódo muda o estado do jogo e limpa a tela, para evitar bugs visuais
    */
    void changeStage(GameStage newStage) {
        stage = newStage;
        system("cls");
    }

    /**
    * Este metódo muda o estado do jogo e limpa a tela, para evitar bugs visuais
    */
    void togglePause() {
        isGamePaused = !isGamePaused;
        system("cls");
    }

    void initNewGame() {
        MapManager::loadLevel(2);
        MapLoader::loadGameFromMap(MapManager::currentMap);
        changeStage(GameStage::PLAYING);
    }
}

#endif //GAME02_CBP_GAMESTAGEMANAGER_H
