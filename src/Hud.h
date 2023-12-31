//
// Created by caior on 17/10/2023.
//

#ifndef GAME02_CBP_HUD_H
#define GAME02_CBP_HUD_H

#include "utils/StringUtils.h"
#include "enums/GameChar.h"
#include "managers/MapManager.h"
#include "GameStatistics.h"
#include "utils/TimeFormat.h"
#include "utils/HudUtils.h"

namespace Hud {
    int hudSize = 0; // Tamanho do painel HUD

    // Função principal para renderizar o HUD
    void render() {
        hudSize = MapManager::currentMap.getColumns() * 3;

        ConsoleColor::set(Color::LIGHTGRAY);
        HudUtils::renderTopBorder(hudSize);
        HudUtils::renderCenterString("Fase " + to_string(MapManager::currentLevel), hudSize);
        HudUtils::renderDivider(hudSize);
        HudUtils::renderVerticalString("Tempo de jogo: ", TimeFormat::formatIntoString(GameStatistics::gameTime), hudSize);
        HudUtils::renderVerticalString("Bombas colocadas: ", to_string(GameStatistics::amountOfBombsPlaced) + ".", hudSize);
        HudUtils::renderDivider(hudSize);
        HudUtils::renderVerticalString("Bombas do jogador: ", to_string(Player::bombsAmount) + ".", hudSize);
        HudUtils::renderVerticalString("PowerUp de Bombas maiores: ", to_string(Player::specialbomb1) + ".", hudSize);
        HudUtils::renderVerticalString("PowerUp de Bombas Intangiveis: ", to_string(Player::specialbomb2) + ".", hudSize);
        HudUtils::renderVerticalString("Inimigos restantes: ", to_string(Enemies::getAliveEnemiesAmount()) + ".", hudSize);
        cout << endl;
        HudUtils::renderBottomBorder(hudSize);
        ConsoleColor::reset();
        cout << endl;
    }
}

#endif //GAME02_CBP_HUD_H
