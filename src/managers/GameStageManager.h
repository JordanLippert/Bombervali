//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_GAMESTAGEMANAGER_H
#define GAME02_CBP_GAMESTAGEMANAGER_H

#include "MapManager.h"
#include "../enums/GameStage.h"
#include "../map/utils/MapLoader.h"
#include "../GameClear.h"
#include <iostream>

namespace GameStageManager {
    GameStage stage = GameStage::START;
    bool isGamePaused = false;

    /**
     * Verifica se o estágio do jogo é jogável.
     * @return Retorna true se o jogo estiver no estágio de jogo (PLAYING) e não estiver pausado, senão, retorna false.
     */
    bool isPlayable() {
        return stage == GameStage::PLAYING && !isGamePaused;
    }

    /**
     * Altera o estado do jogo e limpa a tela para evitar bugs visuais.
     * @param newStage O novo estágio do jogo.
     */
    void changeStage(GameStage newStage) {
        stage = newStage;
        system("cls");
    }

    /**
     * Altera o estado de pausa do jogo e limpa a tela para evitar bugs visuais.
     */
    void togglePause() {
        isGamePaused = !isGamePaused;
        system("cls");
    }

    /**
     * Muda o mapa do jogo para o nível especificado.
     * @param level O número do novo nível.
     */
    void changeLevel(int level) {
        MapManager::loadLevel(level);
        MapLoader::loadGameFromMap(MapManager::currentMap);
        changeStage(GameStage::PLAYING);
    }

    /**
     * Avança para o próximo nível do jogo, se disponível.
     */
    void nextLevel() {
        int level = MapManager::currentLevel + 1;

        if (level > MapManager::MAX_LEVEL) level = MapManager::MAX_LEVEL;

        changeLevel(level);
    }

    /**
     * Inicializa um novo jogo, limpando quaisquer dados anteriores.
     */
    void initNewGame() {
        GameClear::clean();
        changeLevel(1);
    }
}

#endif //GAME02_CBP_GAMESTAGEMANAGER_H
