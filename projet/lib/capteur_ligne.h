/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: capteur ligne
Description: Cette classe permet au robot de capter la ligne.

*/

#pragma once

#include <avr/io.h>


class CapteurLigne {
    public:
        CapteurLigne();
        uint8_t lirePins();
        bool checkIntersection();
        bool checkIntersectionDirectionelle(bool gauche);
};
