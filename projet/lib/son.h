/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: Son
Description: Cette classe s'occupe de pouvoir jouer des sonorite sur le robot.
Identifications matérielles :
 - Sortie : Pallete sonore
*/

#pragma once
#include <avr/interrupt.h>
#include <avr/io.h>
#include "minuterie.h"
#define F_CPU 8000000
#include <util/delay.h>



class Son
{
public:
    Son();
    ~Son() = default;
    void jouerFrequence(int n);
    void jouerMusique();
    void arreterMusique();
};