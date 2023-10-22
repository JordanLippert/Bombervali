//
// Created by caior on 17/10/2023.
//

#ifndef GAME02_CBP_CONSUMABLES_H
#define GAME02_CBP_CONSUMABLES_H

#include "../utils/Vector.h"
#include "../enums/GameChar.h"
#include "../enums/ConsumableType.h"

struct Consumable {
    int row;
    int column;
    ConsumableType type;

    bool isInLocation(int locRow, int locColumn) const {
        return row == locRow && locColumn == column;
    }
};

namespace Consumables {
    Vector<Consumable> consumables;

    /**
     * Coloca um novo consumível na posição especificada.
     * @param row A linha onde o consumível será colocado.
     * @param column A coluna onde o consumível será colocado.
     * @param type O tipo de consumível a ser colocado.
     */
    void placeNew(int row, int column, ConsumableType type) {
        Consumable newConsumable {};

        newConsumable.row = row;
        newConsumable.column = column;
        newConsumable.type = type;

        consumables.push(newConsumable);
    }

    /**
     * Verifica se existe um consumível na localização especificada.
     * @param row A linha da localização a ser verificada.
     * @param column A coluna da localização a ser verificada.
     * @return Retorna true se um consumível for encontrado na localização, senão retorna false.
     */
    bool existsConsumableAtLocation(int row, int column) {
        for (int i = 0; i < consumables.getSize(); ++i) {
            Consumable current = consumables[i];

            if (current.isInLocation(row, column)) {
                return true;
            }
        }

        return false;
    }

    /**
     * Pega o consumível na localização especificada.
     * @param row A linha da localização do consumível desejado.
     * @param column A coluna da localização do consumível desejado.
     * @return Retorna o consumível encontrado na localização.
     */
    Consumable getConsumableByLocation(int row, int column) {
        for (int i = 0; i < consumables.getSize(); ++i) {
            Consumable current = consumables[i];

            if (current.isInLocation(row, column)) {
                return current;
            }
        }
    }

    /**
     * Remove um consumível na localização especificada.
     * @param row A linha da localização do consumível desejado.
     * @param column A coluna da localização do consumível desejado.
     */
    void deleteConsumableByLocation(int row, int column) {
        for (int i = 0; i < consumables.getSize(); ++i) {
            Consumable current = consumables[i];

            if (current.isInLocation(row, column)) {
                consumables.remove(i);
            }
        }
    }

    /**
     * Pega o índice do consumível na localização especificada.
     * @param row A linha da localização do consumível desejado.
     * @param column A coluna da localização do consumível desejado.
     * @return Retorna o índice do consumível encontrado na localização.
     */
    int getConsumableIndex(int row, int column) {
        for (int i = 0; i < consumables.getSize(); ++i) {
            Consumable current = consumables[i];

            if (current.isInLocation(row, column)) {
                return i;
            }
        }

        return 0;
    }

    /**
     * Obtém o caractere associado ao consumível no índice especificado.
     * @param index O índice do consumível.
     * @return Retorna o caractere associado ao consumível.
     */
    char getConsumableChar(int index) {
        ConsumableType type = consumables[index].type;

        switch (type) {
            case ConsumableType::BOMB:

                return char(GameChar::BOMB_CONSUMABLE);

            case ConsumableType::POWER_UP_DISTANCE:
                return char(GameChar::POWER_UP_DISTANCE_BOOST);

            case ConsumableType::POWER_UP_IGNORE_WALLS:
                return char(GameChar::POWER_UP_IGNORE_WALLS);
        }

        return 0;
    }

    Color getConsumableColor(int index) {
        ConsumableType type = consumables[index].type;

        switch (type) {
            case ConsumableType::BOMB:
                return Color::CYAN;
            case ConsumableType::POWER_UP_DISTANCE:
                return Color::LIGHT_BLUE;
            case ConsumableType::POWER_UP_IGNORE_WALLS:
                return Color::LIGHT_MAGENTA;
        }

        return Color::LIGHTGRAY;
    }
}

#endif //GAME02_CBP_CONSUMABLES_H
