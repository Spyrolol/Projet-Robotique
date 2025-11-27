
#include "logique_fourchette.h"

void LogiqueFourchette::stockageDirection()
{
    // RAPPEL CONSIGNE :
    // bouton blanc : passer à gauche
    // bouton Interrupt : passer à droite

    uint8_t valeurEnregistreCompteur = 0;

    while (valeurEnregistreCompteur < 2)
    {
        if (robot_.boutonBreadboardAppuye())
        {
            directionEnregistre[valeurEnregistreCompteur++] = 1; // 0 pour droite, 1 pour gauche
            while (robot_.boutonBreadboardAppuye())
            {
                robot_.allumerRouge();
            }
        }
        if (robot_.boutonAppuyer())
        {
            directionEnregistre[valeurEnregistreCompteur++] = 0; // 0 pour droite, 1 pour gauche
            while (robot_.boutonAppuyer())
            {
                robot_.allumerVert();
            }
        }
        robot_.eteindreLumiere();
    }
    directionConfirme = true;

    _delay_ms(2000);
}

void LogiqueFourchette::pointBC()
{
    // partie BC

    // 1e cas bouton
    if (directionEnregistre[0] == 1)
     {
        logique.prioriteGauche = true;
        logique.prioriteDroite = false;
        while (robot_.lirePins() != 0)
        {
            logique.mouvementAutomatique(90);
        }

        robot_.avancer(100);
        _delay_ms(1000);
        robot_.eteindre();

        robot_.jouerFrequence(45);
        _delay_ms(1000);
        robot_.arreterMusique();

        while (robot_.lirePins() == 0)
        {
            robot_.tournerGauche(255, false);
            _delay_ms(10);
            robot_.tournerGauche(80, false); 
            _delay_ms(50);
        }



        while (robot_.lirePins() != 0)
        {
            logique.mouvementAutomatique(90);
        }
    }

    // 2e cas bouton
    if (directionEnregistre[0] == 0)
    {
        logique.prioriteDroite = true;
        logique.prioriteGauche = false;

        while (robot_.lirePins() != 0)
        {
            logique.mouvementAutomatique(90);
        }

        robot_.avancer(100);
        _delay_ms(1000);
        robot_.eteindre();
        robot_.jouerFrequence(45);
        _delay_ms(1000);
        robot_.arreterMusique();

        while (robot_.lirePins() == 0)
        {
            robot_.tournerDroite(255, false);
            _delay_ms(10);
            robot_.tournerDroite(80, false); 
            _delay_ms(50);
        }

        while (robot_.lirePins() != 0)
        {
            logique.mouvementAutomatique(90);
        }
    }

    // 3e cas bouton
    if (directionEnregistre[1] == 1)
    {
        logique.prioriteGauche = true;
        logique.prioriteDroite = false;
        while (robot_.lirePins() != 0)
        {
            logique.mouvementAutomatique(90);
        }

          robot_.avancer(100);
        _delay_ms(1000);
        robot_.eteindre();
         robot_.jouerFrequence(45);
        _delay_ms(1000);
        robot_.arreterMusique();

        while (robot_.lirePins() == 0)
        {
            robot_.tournerGauche(255, false);
            _delay_ms(10);
            robot_.tournerGauche(80, false); 
            _delay_ms(50);
        }
        while (robot_.lirePins() != 0)
        {
            logique.mouvementAutomatique(90);
        }
        while (robot_.lirePins() == 0)
        {
            robot_.tournerDroite(255, false);
            _delay_ms(10);
            robot_.tournerDroite(80, false); 
            _delay_ms(50);
        }

    }

    // 4e cas bouton
    if (directionEnregistre[1] == 0)
    {
        logique.prioriteDroite = true;
        logique.prioriteGauche = false;
        while (robot_.lirePins() != 0)
        {
            logique.mouvementAutomatique(90);
        }

         robot_.avancer(100);
        _delay_ms(1000);
        robot_.eteindre();
         robot_.jouerFrequence(45);
        _delay_ms(1000);
        robot_.arreterMusique();

        while (robot_.lirePins() == 0)
        {
            robot_.tournerDroite(255, false);
            _delay_ms(10);
            robot_.tournerDroite(80, false); 
            _delay_ms(50);
        }
        while (robot_.lirePins() != 0)
        {
            logique.mouvementAutomatique(90);
        }
        while (robot_.lirePins() == 0)
        {
            robot_.tournerGauche(255, false);
            _delay_ms(10);
            robot_.tournerGauche(80, false); 
            _delay_ms(50);
        }
    }
    
    robot_.eteindre();
}