#include "logiqueLabyrinthe.h"

// Définir les broches de la DEL
const uint8_t DEL_ROUGE = PA0;
const uint8_t DEL_VERTE = PA1;
const uint8_t DISTANCE_POTEAU = 150;
const uint8_t VITESSE_RECENTRER = 175;
const uint8_t VITESSE_ANALYSE = 175;
#define D1 0x01 // 00001
#define D2 0x02 // 00010
#define D3 0x04 // 00100
#define D4 0x08 // 01000
#define D5 0x10 // 10000
#define TOUR_VITESSE 100
#define TOUR_DELAY 50
#define TORQUE_STARTUP 10

// Methode pour tourner sans reoturner dans boucle,donc on tourne thats it

// Constructeur
LogiqueLabyrinthe::LogiqueLabyrinthe(LogiqueRobot &robot)
    : logique_(robot), robot_(robot.getRobot()) {}

void LogiqueLabyrinthe::sequenceDetectionPoteau()
{
    robot_.eteindre();
    for (int i = 0; i < 8; i++)
    {
        robot_.allumerVert();
        _delay_ms(125);
        robot_.eteindreLumiere();
        _delay_ms(125);
    }
}

void LogiqueLabyrinthe::revenirCentreDepuisDroite()
{
    robot_.tournerGauche(160, true);
    _delay_ms(100);
    while (true)
    {
        robot_.tournerGauche(VITESSE_RECENTRER, true); //  revient vers le centre
        _delay_ms(120);
        robot_.eteindre();

        // Lire les capteurs du sol
        uint8_t capteurs = robot_.lirePins() & 0x1F;

        // Tester si les capteurs du centre (D3, D2, D4) sont allumés
        if (capteurs & (D3))
            break;

        _delay_ms(100);
    }

    robot_.eteindre();
    _delay_ms(200); // petite pause pour stabilité
}

void LogiqueLabyrinthe::revenirCentreDepuisGauche()
{
    robot_.tournerDroite(160, true);
    _delay_ms(100);
    while (true)
    {
        robot_.tournerDroite(VITESSE_RECENTRER, true); //  revient vers le centre
        _delay_ms(120);
        robot_.eteindre();

        uint8_t capteurs = robot_.lirePins() & 0x1F;

        // Si on retrouve bien D3, D2 et D4 → stop
        if (capteurs & (D3))
            break;

        _delay_ms(100);
    }

    robot_.eteindre();
    _delay_ms(200);
}

void LogiqueLabyrinthe::scanDroiteTerminator(bool &obstacleTrouve)
{
    robot_.tournerDroite(180, true);
    _delay_ms(120);
    while (!(robot_.lirePins() & D5))
    {
        robot_.tournerDroite(VITESSE_ANALYSE, true);
        _delay_ms(120);
        robot_.eteindre();

        _delay_ms(100); // Stabilisation du robot

        if ((robot_.lireValeurMoyenne(5) > 150))
        {
            obstacleTrouve = true;
        }

        _delay_ms(100); // petit délai avant la prochaine itération
    }

    robot_.eteindre();
    _delay_ms(150);
}

void LogiqueLabyrinthe::scanGaucheTerminator(bool &obstacleTrouve)
{
    robot_.tournerGauche(180, true);
    _delay_ms(120);
    while (!(robot_.lirePins() & D1))
    {
        robot_.tournerGauche(VITESSE_ANALYSE, true);
        _delay_ms(120);
        robot_.eteindre();

        _delay_ms(100); // Stabilisation du robot

        if ((robot_.lireValeurMoyenne(5) > 150))
        {
            obstacleTrouve = true;
        }

        _delay_ms(100);
    }

    robot_.eteindre();
    _delay_ms(150);
}

void LogiqueLabyrinthe::detectionPoteau()
{
    // uint8_t nbrIntersction = 0;
    robot_.eteindre();
    robot_.avancer(160);
    _delay_ms(800);

    //  Regarde vers le haut
    scanDroiteTerminator(obstacleHaut); //  Ajoute le scan dynamique
    robot_.eteindre();
    _delay_ms(400);
    // Revient center
    revenirCentreDepuisDroite();
    robot_.eteindre();
    _delay_ms(400);
    //  Regarde vers le bas
    robot_.eteindre();
    scanGaucheTerminator(obstacleBas); //  Ajoute le scan dynamique
    robot_.eteindre();
    _delay_ms(400);
    // Revient center
    revenirCentreDepuisGauche();
    robot_.eteindre();
    _delay_ms(400);
    logique_.scanCentre(obstacleMilieu); //  Ajoute le scan dynamique
    robot_.eteindre();
}
// Cest la logique pour avancer dans parcours

void LogiqueLabyrinthe::executer()
{
    bool reculer = true;
    detectionPoteau();

    robot_.eteindre();
    _delay_ms(300);

    // ICI ON REVIENT AU CNETRE POUR ARRIVER FACE AU DEUXIME COLLOGNE POTEAU
    //  Choisir action selon la position des obstacles
    //   do

    // premier if
    if (obstacleHaut && obstacleMilieu)
    {
        // trouver la ligne dans la bonne direction
        robot_.tournerGauche(170, true);
        _delay_ms(600);

        while (robot_.lirePins() == 0)
        {
            robot_.tournerGauche(255, true);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerGauche(TOUR_VITESSE, true);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        sequenceDetectionPoteau();
        _delay_ms(400);

        // Descendre
        while (!robot_.checkIntersectionDirectionelle(false))
        {
            logique_.mouvementAutomatique(90);
        }

        // Sauter la ligne
        robot_.avancer(160);
        _delay_ms(600);

        // tourner jusqu'on retrouve la ligne
        while (robot_.lirePins() == 0)
        {
            robot_.tourDroiteSharp(255);
            _delay_ms(TORQUE_STARTUP);
            robot_.tourDroiteSharp(TOUR_VITESSE);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);

        // avancer jusqu'à la prochaine ligne
        while (!robot_.checkIntersectionDirectionelle(false))
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(500);

        // avancer jusqu'à la prochaine ligne
        while (!robot_.checkIntersectionDirectionelle(false))
        {
            logique_.mouvementAutomatique(90);
        }

        // retourner vers le centre
        robot_.avancer(160);
        _delay_ms(1100);
        robot_.tournerDroite(170, true);
        _delay_ms(400);

        while (robot_.lirePins() == 0)
        {
            robot_.tournerDroite(255, true);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerDroite(TOUR_VITESSE, true);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);

        // avancer jusqu'au centre
        while (!robot_.checkIntersection())
        {
            logique_.mouvementAutomatique(90);
        }

        // aligner avec le centre
        robot_.avancer(160);
        _delay_ms(1100);
        robot_.tournerGauche(170, true);
        _delay_ms(450);

        while ((robot_.lirePins() & 14) == 0)
        {
            robot_.tournerGauche(255, true);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerGauche(TOUR_VITESSE, true);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);
    }

    else if (obstacleBas && obstacleMilieu)
    {
        // trouver la ligne dans la bonne direction
        robot_.tournerDroite(170, true);
        _delay_ms(600);

        while (robot_.lirePins() == 0)
        {
            robot_.tournerDroite(255, true);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerDroite(TOUR_VITESSE, true);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);
        sequenceDetectionPoteau();

        // monter
        while (!robot_.checkIntersectionDirectionelle(true))
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(600);

        // tourner jusqu'on retrouve la ligne
        while (robot_.lirePins() == 0)
        {
            robot_.tourGaucheSharp(255);
            _delay_ms(TORQUE_STARTUP);
            robot_.tourGaucheSharp(TOUR_VITESSE);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);

        // avancer jusqu'à la prochaine ligne
        while (!robot_.checkIntersectionDirectionelle(true))
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(500);

        // avancer jusqu'à la prochaine ligne
        while (!robot_.checkIntersectionDirectionelle(true))
        {
            logique_.mouvementAutomatique(90);
        }

        // retourner vers le centre
        robot_.avancer(160);
        _delay_ms(1100);
        robot_.tournerGauche(170, true);
        _delay_ms(400);

        while (robot_.lirePins() == 0)
        {
            robot_.tournerGauche(255, true);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerGauche(TOUR_VITESSE, true);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);

        // avancer jusqu'au centre
        while (!robot_.checkIntersection())
        {
            logique_.mouvementAutomatique(90);
        }

        // aligner avec le centre
        robot_.avancer(160);
        _delay_ms(1100);
        robot_.tournerDroite(170, true);
        _delay_ms(450);

        while ((robot_.lirePins() & 14) == 0)
        {
            robot_.tournerDroite(255, true);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerDroite(TOUR_VITESSE, true);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);
    }

    else
    {

        sequenceDetectionPoteau();
        robot_.avancer(160); // avance pour bien se placer sur la ligne
        _delay_ms(400);

        // avancer jusqu'à la prochaine intersection
        while (!robot_.checkIntersection())
        {
            logique_.mouvementAutomatique(90);
        }

        robot_.avancer(160);
        _delay_ms(400);

        // déplacer jusqu'à destination
        while (!robot_.checkIntersection())
        {
            logique_.mouvementAutomatique(90);
        }

        robot_.eteindre();
        reculer = false;
    }

    if (reculer)
    {
        robot_.reculer(160);
        _delay_ms(1200);
        robot_.eteindre();
    }

    _delay_ms(400);

    obstacleBas = false;
    obstacleHaut = false;
    obstacleMilieu = false;
    detectionPoteau();

    // deuxieme if
    if (obstacleHaut && obstacleMilieu)
    {
        // trouver la ligne dans la bonne direction
        robot_.tournerGauche(170, true);
        _delay_ms(600);

        while (robot_.lirePins() == 0)
        {
            robot_.tournerGauche(255, true);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerGauche(TOUR_VITESSE, true);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);
        sequenceDetectionPoteau(); // billel (clignore rouge)
        // Descendre
        while (!robot_.checkIntersectionDirectionelle(false))
        {
            logique_.mouvementAutomatique(90);
        }

        // Sauter la ligne
        robot_.avancer(160);
        _delay_ms(600);

        // tourner jusqu'on retrouve la ligne
        while (robot_.lirePins() == 0)
        {
            robot_.tourDroiteSharp(255);
            _delay_ms(TORQUE_STARTUP);
            robot_.tourDroiteSharp(TOUR_VITESSE);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);

        // avancer jusqu'à la prochaine ligne
        while (!robot_.checkIntersectionDirectionelle(false))
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(500);

        // avancer jusqu'à la prochaine ligne
        while (!robot_.checkIntersectionDirectionelle(false))
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(500);

        // tourner jusqu'on retrouve la ligne
        while (robot_.lirePins() == 0)
        {
            robot_.tourDroiteSharp(255);
            _delay_ms(TORQUE_STARTUP);
            robot_.tourDroiteSharp(TOUR_VITESSE);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);

        // avancer jusqu'au centre
        while (!robot_.checkIntersectionDirectionelle(false))
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(500);

        // avancer jusqu'au dernier intersection
        while (!robot_.checkIntersectionDirectionelle(false))
        {
            logique_.mouvementAutomatique(90);
        }

        // sortir du labyrinthe
        robot_.avancer(160);
        _delay_ms(500);

        robot_.eteindre();
        return;
    }

    else if (obstacleBas && obstacleMilieu)
    {
        // trouver la ligne dans la bonne direction
        robot_.tournerDroite(170, true);
        _delay_ms(600);

        while (robot_.lirePins() == 0)
        {
            robot_.tournerDroite(255, true);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerDroite(TOUR_VITESSE, true);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);
        sequenceDetectionPoteau();

        // monter
        while (!robot_.checkIntersectionDirectionelle(true))
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(600);

        // tourner jusqu'on retrouve la ligne
        while (robot_.lirePins() == 0)
        {
            robot_.tourGaucheSharp(255);
            _delay_ms(TORQUE_STARTUP);
            robot_.tourGaucheSharp(TOUR_VITESSE);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);

        // avancer jusqu'à la prochaine ligne
        while (!robot_.checkIntersectionDirectionelle(true))
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(500);

        // avancer jusqu'à la prochaine ligne
        while (!robot_.checkIntersection())
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(500);

        // tourner jusqu'on retrouve la ligne et sortir du laby
        while (robot_.lirePins() == 0)
        {
            robot_.tourDroiteSharp(255);
            _delay_ms(TORQUE_STARTUP);
            robot_.tourDroiteSharp(TOUR_VITESSE);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);
        return;
    }

    else
    {
        sequenceDetectionPoteau();
        robot_.avancer(160); // avance pour bien se placer sur la ligne
        _delay_ms(400);

        // avancer jusqu'à la prochaine intersection
        while (!robot_.checkIntersection())
        {
            logique_.mouvementAutomatique(90);
        }

        robot_.avancer(160);
        _delay_ms(400);

        // déplacer jusqu'à destination
        while (!robot_.checkIntersection())
        {
            logique_.mouvementAutomatique(90);
        }

        // sauter la ligne
        robot_.avancer(160);
        _delay_ms(600);

        // tourner jusqu'on retrouve la ligne
        while (robot_.lirePins() == 0)
        {
            robot_.tourDroiteSharp(255);
            _delay_ms(TORQUE_STARTUP);
            robot_.tourDroiteSharp(TOUR_VITESSE);
            _delay_ms(TOUR_DELAY);
        }

        robot_.eteindre();
        _delay_ms(400);

        // avancer jusqu'à dernière intersection dans laby
        while (!robot_.checkIntersectionDirectionelle(false))
        {
            logique_.mouvementAutomatique(90);
        }

        // sortir de laby
        robot_.avancer(160);
        _delay_ms(500);

        robot_.eteindre();
        return;
    }
}