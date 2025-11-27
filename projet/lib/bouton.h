/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: Bouton
Description: Cette classe permet de savoir si le bouton du breadboard ou du robot est appuyé.

*/

#pragma once

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

#define DELAY_MS 50




class Bouton {
    public:
        Bouton();
        bool boutonAppuyer();
        bool boutonBreadboardAppuye();
    private:
    
};