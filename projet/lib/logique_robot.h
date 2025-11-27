/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: logiqueRobot
Description: Cette classe s'occupe de configurer les différents éléments branchés au robot pour qu'avec une seul instanciation de robot, on puisse actionner
les moteurs, gérer les LEDs, capter la ligne, gérer le bouton, jouer un son et détecter les poteaux. 

*/

#pragma once

#include "robot.h"
#include "capteurPoteaux.h"

class LogiqueRobot
{
public:
    LogiqueRobot(Robot &robot) : robot_(robot), gaucheDerniereDirection(false) {};
    bool boutonAppuyer();
    Robot &getRobot()
    {
        return robot_;
    }

    void mouvementAutomatique(uint8_t dutyCycle);

    void scanCentre(bool &obstacleTrouve);

    void tournerDroiteJusquaProchaineLigne();
    void tournerGaucheJusquaProchaineLigne();

    bool prioriteGauche = false;
    bool prioriteDroite = false;

private:
    Robot &robot_;
    bool gaucheDerniereDirection;
};