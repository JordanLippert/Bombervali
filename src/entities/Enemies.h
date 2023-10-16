//
// Created by caio on 29/08/2023.
//

#ifndef GAME02_ENEMIES_H
#define GAME02_ENEMIES_H
#include <cstdlib>
#include <ctime>
#include "../utils/Vector.h"
#include "../managers/MapManager.h"

struct Enemy {
    int row;
    int column;
    bool isLive;
    bool hasPlacedBomb;
};

namespace Enemies {
    clock_t end, start;
    int duration;
    bool startedTimer = false;

    Vector<Enemy> enemies;

    /**
     * Verifica se existe um inimigo na localização informada
     * @param row Linha da localização
     * @param column Coluna da localização
     */
    bool thereIsEnemy(int row, int column){
        for(int i = 0; i < enemies.getSize(); i++){
            Enemy enemy = enemies[i];

            if (enemy.row == row && enemy.column == column && enemy.isLive){
                return true;
            }
        }

        return false;
    }

    int getAliveEnemiesAmount() {
        int amount = 0;

        for (int i = 0; i < enemies.getSize(); ++i) {
            Enemy enemy = enemies[i];

            if (enemy.isLive) amount++;
        }

        return amount;
    }

    // Está função deve retornar se todos os inimigos estão mortos
    bool areAllEnemiesDead() {
        for (int i = 0; i < enemies.getSize(); ++i) {
            Enemy enemy = enemies[i];

            if (enemy.isLive) return false;
        }

        return true;
    }

    // Está função retorna um número gerado com o limite informado
    int generateNumber(int maxNumber = 3) {
        return rand() % maxNumber;
    }

    // Função para mover os inimigos para cima
    void moveEnemyUp(Enemy &enemy) {
        if (MapManager::canMove(enemy.row - 1, enemy.column)) {
            enemy.row--;
        }
    }

    // Função para mover os inimigos para baixo
    void moveEnemyDown(Enemy &enemy) {
        if (MapManager::canMove(enemy.row + 1, enemy.column)) {
            enemy.row++;
        }
    }

    //Função para mover inimigos para esquerda
    void moveEnemyLeft(Enemy &enemy) {
        if (MapManager::canMove(enemy.row, enemy.column - 1)) {
            enemy.column--;
        }
    }

    //Função para mover inimigos para direita
    void moveEnemyRight(Enemy &enemy) {
        if (MapManager::canMove(enemy.row, enemy.column + 1)) {
            enemy.column++;
        }
    }

    // Função para mover os inimigos de forma randômica
    void moveEnemies() {
        int i;
        for (i = 0; i < enemies.getSize(); i++) {
            Enemy currentEnemy = enemies[i];

            if (!currentEnemy.isLive) continue;

            int amountOfTiles = generateNumber() + 1;
            int direction = generateNumber(4);

            for (int j = 0; j < amountOfTiles; ++j) {
                switch (direction) {
                    case 0:
                        moveEnemyUp(currentEnemy);
                        break;
                    case 1:
                        moveEnemyDown(currentEnemy);
                        break;
                    case 2:
                        moveEnemyLeft(currentEnemy);
                        break;
                    case 3:
                        moveEnemyRight(currentEnemy);
                        break;
                }

                enemies[i] = currentEnemy;
            }
        }
    }

    // Função para colocar as bombas inimigas
    void placeBombs() {
        for (int i = 0; i < enemies.getSize(); ++i) {
            Enemy enemy = enemies[i];

            if (!enemy.isLive) continue;

            int randomNumber = generateNumber(100) + 1;

            if (randomNumber <= 10 && !enemy.hasPlacedBomb) {
                Bombs::placeBomb(enemy.row, enemy.column, i);

                enemy.hasPlacedBomb = true;
                enemies[i] = enemy;
            }
        }
    }

    /**
     * Função para verificar se existe uma explosão perto de um inimigo
     */
    void killEnemies() {
        for (int i = 0; i < enemies.getSize(); ++i) {
            Enemy enemy = enemies[i];

            if (enemy.isLive && Bombs::isExplosionNear(enemy.row, enemy.column)) {
                enemy.isLive = false;

                enemies[i] = enemy;
            }
        }
    }

    /**
     * Função responsável pela lógica dos inimigos (roda no Loop principal)
     */
    void tick() {
        if (enemies.getSize() == 0) return;
        killEnemies();

        // Resetar o ínicio do clock caso necessário
        if (duration == 0 && !startedTimer) {
            start = clock();
            startedTimer = true;
        }

        end = clock();
        // Calcular duração do ciclo
        duration = (end - start) / CLOCKS_PER_SEC;

        if (duration == 1) {
            duration = 0;
            // Variável para controlar se o contador deve reiniciar
            startedTimer = false;

            // Mover e colocar as bombas dos inimigos
//            placeBombs();
            moveEnemies();
        }
    }
}

#endif //GAME02_ENEMIES_H
