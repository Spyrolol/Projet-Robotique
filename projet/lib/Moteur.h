/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final : Motors
Description: Cette classe s'occupe de configurer la génération d'un signal PWM, une méthode permettant de contrôler la direction des roues (soit gauche ou droite)
              et les différentes possibilités de déplacement du robot (soit avancer, reculer ou arrêter).
Identifications matérielles :
Sortie : Broche 5 à 8 (PD4 à PD7) où PD6 et PD7 sont les sorties du signal PWM.
*/
#pragma once
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

class Moteur
{
public:
    Moteur();
    void initialisation();
    void avancer(uint8_t dutyCycle);
    void reculer(uint8_t dutyCycle);
    void eteindre();
    void tournerDroite90();
    void tournerGauche90();
    void tournerDroite(uint8_t dutyCycle, bool surPlace);
    void tournerGauche(uint8_t dutyCycle, bool surPlace);
    void tourDroiteSharp(uint8_t dutyCycle);
    void tourGaucheSharp(uint8_t dutyCycle);
};