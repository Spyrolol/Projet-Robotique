/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: logique maison
Description: Cette classe s'occupe de gérer les mouvements et les décisions du robot dans l'épreuve de la maison.

*/

#pragma once

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "robot.h"
#include "logique_robot.h"

class LogiqueRobot;

class LogiqueMaison
{
public:
    LogiqueMaison(LogiqueRobot &robot) : logique_(robot), robot_(robot.getRobot()) {};
    void runMaison();
    void sequenceDetectionPoteau(bool poteau);
    void tournerDroiteJusquaProchaineLigne();
    void tournerGaucheJusquaProchaineLigne();

private:
    LogiqueRobot &logique_;
    Robot &robot_;
};