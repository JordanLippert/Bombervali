//
// Created by Caio on 18/10/2023.
//

#ifndef GAME02_CBP_MENUOPTIONTYPE_H
#define GAME02_CBP_MENUOPTIONTYPE_H

#include <string>

enum class MenuOptionType {
    NEW_GAME,
    LOAD_GAME,
    SAVE_GAME,
    CREDITS,
    CLOSE_GAME,
    RETURN_TO_START,
    RETURN_TO_GAME,
};

std::string getTextFromType(MenuOptionType type) {
    switch (type) {
        case MenuOptionType::NEW_GAME: {
            return "Novo Jogo";
        }
        case MenuOptionType::LOAD_GAME: {
            return "Carregar Jogo";
        }
        case MenuOptionType::SAVE_GAME: {
            return "Salvar Jogo";
        }
        case MenuOptionType::CREDITS: {
            return "Desenvolvedores";
        }
        case MenuOptionType::CLOSE_GAME: {
            return "Sair";
        }
        case MenuOptionType::RETURN_TO_GAME: {
            return "Voltar ao Jogo";
        }        case MenuOptionType::RETURN_TO_START: {
            return "Voltar ao menu";
        }
    }

    return "PLACEHOLDER_TEXT";
}


#endif //GAME02_CBP_MENUOPTIONTYPE_H
