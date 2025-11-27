/*
 * Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
 * Groupe: 04
 * Projet final: Led

 * Description: Classe déclarant plusieurs méthodes pour s'assurer du contrôle de la DEL. Permet d'allumer la DEL en différentes couleurs
                tout en laissant le choix à l'utilisateur des broches auxquels il souhaite connecter la DEL libre.
 * Identifications matérielles :
 - Sortie : DEL-Libre
 - Sortie : Port et broches déterminés au choix
*/
#pragma once

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

class Led
{
public:
    Led( volatile uint8_t *portx,  volatile uint8_t *ddrx, const uint8_t rougePin, const uint8_t vertPin);
    ~Led() = default;
    void allumerRouge();
    void allumerVert();
    void alternerDEL_2HZ();
    void allumerAmbre();
    void eteindreLumiere();
protected:
    volatile uint8_t *portx_;

    uint8_t rougePin_;
    uint8_t vertPin_;
    
    static constexpr double ROUGE_AMBRE_DELAI_MS = 5.0;
    static constexpr double VERT_AMBRE_DELAI_MS = 10.0;
};