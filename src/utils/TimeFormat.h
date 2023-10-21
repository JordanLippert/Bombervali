//
// Created by Caio on 16/10/2023.
//

#ifndef GAME02_CBP_TIMEFORMAT_H
#define GAME02_CBP_TIMEFORMAT_H

#include <string>

/**
 * Estrutura que representa minutos e segundos.
 */
struct SecondsAndMinutes {
    int minutes; // Minutos
    int seconds; // Segundos
};

namespace TimeFormat {
    /**
     * Formata um valor total de segundos em minutos e segundos separados.
     * @param totalSeconds O valor total de segundos.
     * @return Uma estrutura SecondsAndMinutes com os minutos e segundos formatados.
     */
    SecondsAndMinutes format(int totalSeconds) {
        SecondsAndMinutes formatted {};

        formatted.minutes = totalSeconds / 60; // Calcula os minutos.
        formatted.seconds = totalSeconds % 60; // Calcula os segundos restantes.

        return formatted;
    }

    /**
     * Formata um valor total de segundos em uma string descritiva, como "2 minutos e 30 segundos".
     * @param totalSeconds O valor total de segundos.
     * @return Uma string formatada descrevendo os minutos e segundos.
     */
    std::string formatIntoString(int totalSeconds) {
        SecondsAndMinutes secondsAndMinutes = format(totalSeconds);

        int minutes = secondsAndMinutes.minutes;
        int seconds = secondsAndMinutes.seconds;

        if (seconds == 0 && minutes == 0) return "0 segundos."; // Caso especial: 0 segundos.

        std::string formatted;

        if (minutes > 0) {
            formatted += std::to_string(minutes);
            formatted += " ";
            if (secondsAndMinutes.minutes == 1) {
                formatted += "minuto";
            } else {
                formatted += "minutos";
            }
        }

        if (minutes > 0 && seconds > 0) {
            formatted += " e ";
        }

        if (seconds > 0) {
            formatted += std::to_string(seconds);
            formatted += " ";
            if (secondsAndMinutes.seconds == 1) {
                formatted += "segundo";
            } else {
                formatted += "segundos";
            }
        }
        formatted += ".";

        return formatted;
    }
}

#endif //GAME02_CBP_TIMEFORMAT_H
