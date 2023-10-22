//
// Created by caio on 29/08/2023.
//

#ifndef GAME02_ENEMIES_H
#define GAME02_ENEMIES_H
#include <cstdlib>
#include <ctime>
#include "../utils/Vector.h"
#include "../managers/MapManager.h"

// Está função retorna um número gerado com o limite informado
int generateNumber(int maxNumber = 3) {
    return rand() % maxNumber;
}

struct Enemy {
    int row;
    int column;
    bool hasPlacedBomb;

    // Função para mover os inimigos para cima
    bool moveUp() {
        if (!MapManager::canMove(row - 1, column)) {
            return false;
        } else {
            row--;
            return true;
        }
    }

    // Função para mover os inimigos para baixo
    bool moveDown() {
        if (!MapManager::canMove(row + 1, column)) {
            return false;
        } else {
            row++;
            return true;
        }
    }

    //Função para mover inimigos para esquerda
    bool moveLeft() {
        if (!MapManager::canMove(row, column - 1)) {
            return false;
        } else {
            column--;
            return true;
        }
    }

    //Função para mover inimigos para direita
    bool moveRight() {
        if (!MapManager::canMove(row, column + 1)) {
            return false;
        } else {
            column++;
            return true;
        }
    }


    void move (bool canMoveUp = true, bool canMoveDown = true, bool canMoveLeft = true, bool canMoveRight = true) {
        int direction = generateNumber(4);

        return;

        if (direction == 0 ) {
            moveUp();
        }
        if (direction == 1 ) {
            moveDown();
        }
        if (direction == 2 ) {
            moveLeft();
        }
        else {
            moveRight();
        }
    }

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

            if (enemy.row == row && enemy.column == column){
                return true;
            }
        }

        return false;
    }

    /**
     * Retorna a quantidade de inimigos vivos.
     * @return O número de inimigos vivos no momento.
     */
    int getAliveEnemiesAmount() {
       return enemies.getSize();
    }

    // Está função deve retornar se todos os inimigos estão mortos
    bool areAllEnemiesDead() {
        return enemies.getSize() == 0;
        }

    // Função para mover os inimigos de forma randômica
    void moveEnemies() {
        int i;
        for (i = 0; i < enemies.getSize(); i++) {
            Enemy currentEnemy = enemies[i];
            int amountOfTiles = generateNumber() + 1;
            for (int j = 0; j < amountOfTiles; j++) {
                currentEnemy.move();
            }
            enemies[i] = currentEnemy;
        }

    }

    // Função para colocar as bombas inimigas
    void placeBombs() {
        for (int i = 0; i < enemies.getSize(); ++i) {
            Enemy enemy = enemies[i];

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

            if (Bombs::isExplosionNear(enemy.row, enemy.column)) {
                enemies.remove(i);

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
