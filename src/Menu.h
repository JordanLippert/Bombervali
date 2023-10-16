//
// Created by caior on 31/08/2023.
//

#ifndef GAME02_MENU_H
#define GAME02_MENU_H

#include <iostream>
#include "enums/GameStage.h"
#include "utils/StringUtils.h"
#include "entities/Enemies.h"
#include "map/GameMap.h"
#include "map/utils/MapReader.h"
#include "utils/Path.h"
#include "map/MapManager.h"

using namespace std;

namespace Menu {
    GameStage stage = GameStage::START;
    bool isGamePaused = false;

    int terminalRows, terminalColumns;

    /**
     * Este método retorna se o estágio do jogo é jogável
     */
    bool isPlayable() {
        return stage == GameStage::PLAYING && !isGamePaused;
    }

    /**
     * Escrever o menu de inicio do jogo no console
     */
    void renderStartMenu() {
        cout << endl << endl;
        cout << centerStringInScreen(".______     ______   .___  ___. .______    _______ .______     ____    ____  ___       __       __ ", terminalColumns) << endl;
        cout << centerStringInScreen("|   _  \\   /  __  \\  |   \\/   | |   _  \\  |   ____||   _  \\    \\   \\  /   / /   \\     |  |     |  |", terminalColumns) << endl;
        cout << centerStringInScreen("|  |_)  | |  |  |  | |  \\  /  | |  |_)  | |  |__   |  |_)  |    \\   \\/   / /  ^  \\    |  |     |  |", terminalColumns) << endl;
        cout << centerStringInScreen("|   _  <  |  |  |  | |  |\\/|  | |   _  <  |   __|  |      /      \\      / /  /_\\  \\   |  |     |  |", terminalColumns) << endl;
        cout << centerStringInScreen("|  |_)  | |  `--'  | |  |  |  | |  |_)  | |  |____ |  |\\  \\----.  \\    / /  _____  \\  |  `----.|  |", terminalColumns) << endl;
        cout << centerStringInScreen("|______/   \\______/  |__|  |__| |______/  |_______|| _| `._____|   \\__/ /__/     \\__\\ |_______||__|", terminalColumns) << endl;
        cout << centerStringInScreen("v 1.0.0", terminalColumns);
        cout << endl;
        cout << centerStringInScreen("Caio Rosa, Guilherme Silvestre & Jordan Lippert @ Univali", terminalColumns);

        cout << endl << endl << centerStringInScreen("Pressione ENTER para iniciar o jogo.", terminalColumns);
    }

    /**
     * Escrever o menu de vitória do jogo no console
     */
    void renderWin() {
        ConsoleColor::set(Color::GREEN);
        cout << endl << endl;
        cout << centerStringInScreen(" __   _____ _____ ___  ___ ___   _   ", terminalColumns) << endl;
        cout << centerStringInScreen(" \\ \\ / /_ _|_   _/ _ \\| _ \\_ _| /_\\  ", terminalColumns) << endl;
        cout << centerStringInScreen("  \\ V / | |  | || (_) |   /| | / _ \\ ", terminalColumns) << endl;
        cout << centerStringInScreen("   \\_/ |___| |_| \\___/|_|_\\___/_/ \\_\\", terminalColumns) << endl;
        ConsoleColor::reset();
        cout << endl;
        cout << centerStringInScreen("OBRIGADO POR JOGAR!", terminalColumns);
        cout << endl;
        cout << centerStringInScreen("Feito por: Caio Rosa, Guilherme Silvestre & Jordan Lippert", terminalColumns);
    }

    /**
     * Escrever o menu de derrota do jogo no console
     */
    void renderLose() {
        ConsoleColor::set(Color::RED);

        cout << endl << endl;
        cout << centerStringInScreen("  ___  ___ ___ ___  ___ _____ _   ", terminalColumns) << endl;
        cout << centerStringInScreen(" |   \\| __| _ \\ _ \\/ _ \\_   _/_\\  ", terminalColumns) << endl;
        cout << centerStringInScreen(" | |) | _||   /   / (_) || |/ _ \\ ", terminalColumns) << endl;
        cout << centerStringInScreen(" |___/|___|_|_\\_|_\\\\___/ |_/_/ \\_\\", terminalColumns) << endl;
        cout << endl;
        ConsoleColor::reset();
        cout << centerStringInScreen("OBRIGADO POR JOGAR!", terminalColumns);
        cout << endl;
        cout << centerStringInScreen("Feito por: Caio Rosa, Guilherme Silvestre & Jordan Lippert", terminalColumns);
    }

    /**
     * Este metódo muda o estado do jogo e limpa a tela, para evitar bugs visuais
     */
    void changeState(GameStage newStage) {
        stage = newStage;
        system("cls");
    }

    /**
     * Método responsável pela lógica dos menus
     * @param pressedKey
     */
    void tick(int pressedKey) {
        // Se está no estágio de início, verifica se apertou ENTER para iniciar
        if (pressedKey == 13 && stage == GameStage::START) {
            MapManager::loadLevel(1);
            changeState(GameStage::PLAYING);
        }

        // Se está jogando, verifica se é para pausar o jogo
        if (pressedKey == 9 && stage == GameStage::PLAYING) {
            isGamePaused = !isGamePaused;
        }

        // Verifica a condição de vitória
        if (stage == GameStage::PLAYING && Enemies::areAllEnemiesDead()) {
            changeState(GameStage::WIN);
        }
    }

    /**
     * Método responsável pela camada de renderização dos menus
     */
    void render() {
        if (stage == GameStage::START) {
            renderStartMenu();
        }

        if (stage == GameStage::PLAYING && isGamePaused) {
            cout << "O jogo ta pausado hein";
        }

        if (stage == GameStage::LOSE) {
            renderLose();
        }

        if (stage == GameStage::WIN) {
            renderWin();
        }
    }
}

#endif //GAME02_MENU_H
