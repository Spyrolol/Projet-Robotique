/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: logiqueLabyrinthe
Description: Cette classe s'occupe de gérer les mouvements et les décisions du robot dans le labyrinthe.

*/

#pragma once

#include <avr/io.h>
#include "capteurPoteaux.h"
#include "capteur_ligne.h"
#include "Moteur.h"
#include "logique_robot.h"
#include "robot.h"
#define F_CPU 8000000
#include <util/delay.h>

class LogiqueLabyrinthe
{
public:
    LogiqueLabyrinthe(LogiqueRobot &robot);
    void scanCentre(bool &obstacleTrouve);
    void executer();

private:
    LogiqueRobot &logique_;
    Robot &robot_;

    void revenirCentreDepuisDroite();
    void revenirCentreDepuisGauche();
    void scanDroiteTerminator(bool &obstacleTrouve);
    void scanGaucheTerminator(bool &obstacleTrouve);
    void detectionPoteau();
    void sequenceDetectionPoteau();
    bool obstacleHaut = false;
    bool obstacleBas = false;
    bool obstacleMilieu = false;
};