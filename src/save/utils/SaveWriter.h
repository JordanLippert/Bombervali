//
// Created by Caio on 18/10/2023.
//

#ifndef GAME02_CBP_SAVEWRITER_H
#define GAME02_CBP_SAVEWRITER_H

#include "../../entities/Player.h"

namespace SaveWriter {
    void write(int saveNumber, string saveName, bool rewrite) {
        int playerRow = Player::row;
        int playerColumn = Player::column;
    }
}

#endif //GAME02_CBP_SAVEWRITER_H
