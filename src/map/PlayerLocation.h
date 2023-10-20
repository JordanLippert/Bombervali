//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_PLAYERLOCATION_H
#define GAME02_CBP_PLAYERLOCATION_H

namespace PlayerLocation {
    int row, column;
    bool reset = true;
}

namespace CurrentPlayerInfo {
    int row, column, bombsAmount;
}

#endif //GAME02_CBP_PLAYERLOCATION_H
