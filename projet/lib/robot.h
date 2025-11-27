/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: Robot
Description: Cette classe s'occupe de configurer les différents éléments branchés au robot pour qu'avec une seul instanciation de robot, on puisse actionner
les moteurs, gérer les LEDs, capter la ligne, gérer le bouton, jouer un son et détecter les poteaux. 
Identifications matérielles :
Sortie : 
    -Moteur : 
        // PD6 / PD7 : DIRECTION (1 = RECULER, 0 = AVANCER)
        // PD4 / PD5 : ENABLE (1 = ON, 0 = OFF)

        // PD4 / PD6 : ROUE DROITE
        // PD5 / PD7 : ROUE GAUCHE

    -Led : PA0 / PA1
    -CapteurLigne : PA6 / PA3 / PA5 / PA4 / PA2
    -Bouton : 
        -PD2 (Interrupt)
        -PB0 / PB1 (Breadboard)
    -Son : PB2 / PB3
    -CapteurPoteaux : PA7

*/

#pragma once

#include "Moteur.h"
#include "LED.h"
#include "capteur_ligne.h"
#include "bouton.h"
#include "son.h"
#include "capteurPoteaux.h"



class Robot : public Moteur, public Led, public CapteurLigne, public Bouton, public Son, public capteurPoteaux
{
public:
    Robot() : Moteur(), Led(&PORTA, &DDRA, PA0, PA1), CapteurLigne(), Bouton(), Son(), capteurPoteaux(PA7) {}
};