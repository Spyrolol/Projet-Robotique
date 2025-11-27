/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: Capteur poteaux
Description: Cette classe permet d'opérer le capteur distance.

*/

#pragma once

#include "can.h"
#include <stdint.h>
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

class capteurPoteaux
{
public:
    capteurPoteaux(uint8_t port);
    ~capteurPoteaux();

    uint16_t lireValeurBrute();
    uint16_t lireValeurMoyenne(uint8_t nbMesures = 5);
    uint8_t convertirEnDistance(uint16_t valeur);
    uint8_t lireDistance();

    bool detecterObjet(uint8_t distance_seuil = 30); // garde l’ancienne
    bool objetEstPresent();                          // nouvelle méthode fiable basée sur ADC brut
    bool objetEstPresent(uint8_t seuil_cm);          // version avec seuil personnalisable

    bool detecter(uint8_t distanceSeuil);

private:
    uint8_t port_;
    can convertisseur_;
};