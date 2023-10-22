//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_PLAYERLOCATION_H
#define GAME02_CBP_PLAYERLOCATION_H

namespace PlayerLocation {
    int row, column, bombsAmount = 5, specialbomb1 = 0, specialbomb2 = 0;
    bool reset = true;
}

namespace CurrentPlayerInfo {
    int row, column, bombsAmount, specialbomb1, specialbomb2;
}

#endif //GAME02_CBP_PLAYERLOCATION_H

