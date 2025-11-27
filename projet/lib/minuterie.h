/*
 * Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
 * Groupe: 04
 * Projet final: minuterie

 * Description: Classe Minuterie : Permet de configurer et de contrôler la minuterie 1 du microcontrôleur.
                Supporte les modes Normal, CTC et PWM rapide.
*/
#pragma once
#include <avr/io.h>
#include "prescaler.h"
#include <avr/interrupt.h>

// Enum des valeur prescaler


class Minuterie
{
public:
    Minuterie(uint8_t numeroMinuterie);
    ~Minuterie();
    void compareA(const uint16_t time);
    void compareB(const uint16_t time);
    void modeNormal();
    void modeCTC();
    void modeRapidePWM();
    void configurerPrescaler(const prescaler prescal);
    void demarrerMinuterie();
    void arreterMinuterie();
protected:
uint8_t numeroMinuterie_;
};