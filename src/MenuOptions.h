//
// Created by Caio on 18/10/2023.
//

#ifndef GAME02_CBP_MENUOPTIONS_H
#define GAME02_CBP_MENUOPTIONS_H

#include <vector>
#include "enums/MenuOptionType.h"
#include "utils/Vector.h"

namespace MenuOptions {
    std::vector<MenuOptionType> startMenu;
    std::vector<MenuOptionType> closeOrReturnMenu;

    void init() {
        startMenu.push_back(MenuOptionType::NEW_GAME);
        startMenu.push_back(MenuOptionType::LOAD_GAME);
        startMenu.push_back(MenuOptionType::CREDITS);
        startMenu.push_back(MenuOptionType::CLOSE_GAME);

        closeOrReturnMenu.push_back(MenuOptionType::RETURN_TO_START);
        closeOrReturnMenu.push_back(MenuOptionType::CLOSE_GAME);
    }
}

#endif //GAME02_CBP_MENUOPTIONS_H
