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
    void moveUp() {
        if (MapManager::canMove(row - 1, column)) {
            row--;
        }
    }

    // Função para mover os inimigos para baixo
    void moveDown() {
        if (MapManager::canMove(row + 1, column)) {
            row++;
        }
    }

    //Função para mover inimigos para esquerda
    void moveLeft() {
        if (MapManager::canMove(row, column - 1)) {
            column--;
        }
    }

    //Função para mover inimigos para direita
    void moveRight() {
        if (MapManager::canMove(row, column + 1)) {
            column++;
        }
    }


    void move(){
        int amountOfTiles = generateNumber() + 1;
        int direction = generateNumber(4);

        switch (direction) {
            case 0:
                moveUp();
                break;
            case 1:
                moveDown();
                break;
            case 2:
                moveRight();
                break;
            case 3:
                moveLeft();
                break;
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
