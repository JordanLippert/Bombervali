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

    void placeNew(int row, int column, ConsumableType type) {
        Consumable newConsumable {};

        newConsumable.row = row;
        newConsumable.column = column;
        newConsumable.type = type;

        consumables.push(newConsumable);
    }

    int getConsumableIndex(int row, int column) {
        for (int i = 0; i < consumables.getSize(); ++i) {
            Consumable current = consumables[i];

            if (current.isInLocation(row, column)) {
                return i;
            }
        }

        return 0;
    }

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
