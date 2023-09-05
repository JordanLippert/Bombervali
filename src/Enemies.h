//
// Created by caior on 29/08/2023.
//

#ifndef GAME02_ENEMIES_H
#define GAME02_ENEMIES_H
#include <cstdlib>
#include <ctime>
#include "Player.h"

struct Enemy {
    int row;
    int column;
    bool isLive;
};

namespace Enemies {
    clock_t end, start;
    int duration;
    bool startedTimer = false;

    Enemy enemies[3];
    bool thereIsEnemy(int row, int column){
        for(int i = 0; i < 3; i++){
            Enemy enemy = enemies[i];
            if (enemy.row == row && enemy.column == column){
                return true;
            }
        }
    }

    // Está função deve retornar se todos os inimigos estão mortos
    bool areAllEnemiesDead() {
        return false;
    }

    int generateNumber(int maxNumber = 3) {
        return rand() % maxNumber;
    }
    // Função para mover os inimigos para cima
    void moveEnemyUp(Enemy &enemy) {
        if (canMove(enemy.row - 1, enemy.column)) {
            enemy.row--;
        }
    }

    // Função para mover os inimigos para baixo
    void moveEnemyDown(Enemy &enemy) {
        if (canMove(enemy.row + 1, enemy.column)) {
            enemy.row++;
        }
    }

    //Função para mover inimigos para esquerda
    void moveEnemyLeft(Enemy &enemy) {
        if (canMove(enemy.row, enemy.column - 1)) {
            enemy.column--;
        }
    }

    //Função para mover inimigos para direita
    void moveEnemyRight(Enemy &enemy) {
        if (canMove(enemy.row, enemy.column + 1)) {
            enemy.column++;
        }
    }

    // Função para mover os inimigos de forma randômica
    void moveEnemies() {
        int i;
        for (i = 0; i < 3; i++) {
            Enemy currentEnemy = enemies[i];
            int direction = generateNumber(4);
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


    // Função para colocar as bombas dos inimigos
    void placeBombs() {

    }

    void tick() {
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
            // Variavel para controlar se o contador deve reiniciar
            startedTimer = false;

            // Mover e colocar as bombas dos inimigos
            moveEnemies();
            placeBombs();
        }
    }

    void initEnemies() {
        Enemy enemy1 {};

        enemy1.row = 19;
        enemy1.column = 1;
        enemy1.isLive = true;

        enemies[0] = enemy1;


        Enemy enemy2 {};
        enemy2.row = 19;
        enemy2.column = 19;
        enemy2.isLive = true;

        enemies[1] = enemy2;

        Enemy enemy3 {};
        enemy3.row = 1;
        enemy3.column = 19;
        enemy3.isLive = true;

        enemies[2] = enemy3;

    }
}

#endif //GAME02_ENEMIES_H
