
#include "logique_maison.h"
#include "logiqueLabyrinthe.h"
// Constantes pour les capteurs (basé sur capteur_ligne.cpp et logique_robot.cpp)
#define D1 0x01 // 00001 - Capteur le plus à gauche (PA6)
#define D2 0x02 // 00010 - Capteur gauche (PA3)
#define D3 0x04 // 00100 - Capteur centre (PA5)
#define D4 0x08 // 01000 - Capteur droit (PA4)
#define D5 0x10 // 10000 - Capteur le plus à droite (PA2)

void LogiqueMaison::sequenceDetectionPoteau(bool poteau){
    robot_.eteindre();
    for (int i =0; i <8; i++){
        if (poteau) {
            robot_.allumerRouge(); 
        }
        else {
            robot_.allumerVert();
        }
        _delay_ms(125);
        robot_.eteindreLumiere();
        _delay_ms(125);
    }
}


void LogiqueMaison::runMaison()
{
    while (true)
    {
        logique_.mouvementAutomatique(90);
        if (robot_.checkIntersection())
        {
            break;
        }
    }
    // POINT E
    robot_.avancer(255);
    _delay_ms(500);

    while (true)
    {
        logique_.mouvementAutomatique(90);
        if (robot_.checkIntersection())
        {
            break;
        }
    }
    // POINT F
    robot_.avancer(255);
    _delay_ms(500);
    robot_.tournerDroite(100, true);
    _delay_ms(500);

    while (true)
    {
        if (robot_.lirePins() != 0)
        {
            robot_.eteindre();
            break;
        }
    }

    while (true)
    {
        logique_.mouvementAutomatique(90);
        if (robot_.checkIntersection())
        {
            break;
        }
    }
    // POINT G
    robot_.avancer(180);
    while (true)
    {
        if (robot_.lirePins() == 0)
        {
            robot_.eteindre();
            break;
        }
    }
    _delay_ms(200);
    robot_.tournerDroite(150, true);
    while (true)
    {
        if (robot_.lirePins() & D3)
        {
            robot_.eteindre();
            break;
        }
    }

    _delay_ms(200);
    // SI IL Y A POTEAU
    bool poteau = false;
    logique_.scanCentre(poteau);

    _delay_ms(200);

    if (poteau)
    {

        sequenceDetectionPoteau(true);
        robot_.tournerDroite(140, true);
        _delay_ms(650);
        while (true)
        {
            if (robot_.lirePins() != 0)
            {
                robot_.eteindre();
                break;
            }
        }
        while (true)
        {
            logique_.mouvementAutomatique(90);
            if (robot_.checkIntersection())
            {
                break;
            }
        }

        // POINT I

        logique_.tournerDroiteJusquaProchaineLigne();

        while (true)
        {
            logique_.mouvementAutomatique(90);
            if (robot_.checkIntersection())
            {
                break;
            }
        }

        // POINT E
        logique_.tournerDroiteJusquaProchaineLigne();

        while (true)
        {
            logique_.mouvementAutomatique(90);
            if (robot_.checkIntersection())
            {
                break;
            }
        }
        // Point F

        robot_.avancer(255);
        _delay_ms(500);
        robot_.eteindre();
        return;
    }

    // PAS DE POTEAU (POINT G)
    else
    {
        sequenceDetectionPoteau(false);
        while (true)
        {
            logique_.mouvementAutomatique(90);
            if (robot_.lirePins() == 0)
            {
                break;
            }
        }
        // POINT H
        logique_.tournerDroiteJusquaProchaineLigne();

        while (true)
        {
            logique_.mouvementAutomatique(90);
            if (robot_.checkIntersection())
            {
                break;
            }
        }

        // POINT I
        robot_.avancer(255);
        _delay_ms(500);
        robot_.tournerDroite(100, true);
        _delay_ms(100);

        while (true)
        {
            if (robot_.lirePins() != 0)
            {
                robot_.eteindre();
                break;
            }
        }
        while (true)
        {
            logique_.mouvementAutomatique(90);
            if (robot_.checkIntersection())
            {
                break;
            }
        }
        // POINT E
        logique_.tournerDroiteJusquaProchaineLigne();

        while (true)
        {
            logique_.mouvementAutomatique(90);
            if (robot_.checkIntersection())
            {
                break;
            }
        }
        // Point F

        robot_.avancer(255);
        _delay_ms(500);
        robot_.eteindre();
        return;
    }
}