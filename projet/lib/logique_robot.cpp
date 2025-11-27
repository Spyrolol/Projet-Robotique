#include "logique_robot.h"
#include "uart.h"

#define MOVE_DELAY 50

#define D1 1
#define D2 2
#define D3 4
#define D4 8
#define D5 16

//#define dutyCycle 90

#define TORQUE_STARTUP 10

#define VITESSE_ANALYSE 175

void LogiqueRobot::mouvementAutomatique(uint8_t dutyCycle)
{
    UART uart;
    uint8_t chemins = robot_.lirePins();

    if (prioriteDroite)
    {

        if (chemins & D4)
        {
            robot_.tournerDroite(255, false);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerDroite(dutyCycle, false);
            _delay_ms(MOVE_DELAY);
            return;
        }
        else if (chemins & D5)
        {
            gaucheDerniereDirection = false;
            robot_.tournerDroite(255, false);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerDroite(dutyCycle, false);
            _delay_ms(MOVE_DELAY);
            return;
        }
    }

    if (prioriteGauche)
    {
        if (chemins & D2)
        {
            robot_.tournerGauche(255, false);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerGauche(dutyCycle, false);
            _delay_ms(MOVE_DELAY);
            return;
        }
        else if (chemins & D1)
        {
            gaucheDerniereDirection = true;
            robot_.tournerGauche(255, false);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerGauche(dutyCycle, false);
            _delay_ms(MOVE_DELAY);
            return;
        }
    }

    if (chemins == D3)
    {
        robot_.avancer(255);
        _delay_ms(TORQUE_STARTUP);
        robot_.avancer(dutyCycle);
        _delay_ms(MOVE_DELAY);
    }

    else if (chemins & D4)
    {
        robot_.tournerDroite(255, false);
        _delay_ms(TORQUE_STARTUP);
        robot_.tournerDroite(dutyCycle, false);
        _delay_ms(MOVE_DELAY);
    }
    else if (chemins & D2)
    {
        robot_.tournerGauche(255, false);
        _delay_ms(TORQUE_STARTUP);
        robot_.tournerGauche(dutyCycle, false);
        _delay_ms(MOVE_DELAY);
        return;
    }
    else if (chemins & D5)
    {
        gaucheDerniereDirection = false;
        robot_.tournerDroite(255, false);
        _delay_ms(TORQUE_STARTUP);
        robot_.tournerDroite(dutyCycle, false);
        _delay_ms(MOVE_DELAY);
    }
    else if (chemins & D1)
    {
        gaucheDerniereDirection = true;
        robot_.tournerGauche(255, false);
        _delay_ms(TORQUE_STARTUP);
        robot_.tournerGauche(dutyCycle, false);
        _delay_ms(MOVE_DELAY);
        // robot_.eteindre();
    }
    else
    {
        if (gaucheDerniereDirection)
        {
            robot_.tournerGauche(255, false);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerGauche(dutyCycle, false);
            _delay_ms(MOVE_DELAY);
        }
        else
        {
            robot_.tournerDroite(255, false);
            _delay_ms(TORQUE_STARTUP);
            robot_.tournerDroite(dutyCycle, false);
            _delay_ms(MOVE_DELAY);
        }
    }
}

void LogiqueRobot::scanCentre(bool &obstacleTrouve)
{
    robot_.tournerDroite(VITESSE_ANALYSE, true);
    _delay_ms(200);

    robot_.eteindre();
    _delay_ms(150);

    // Retour progressif vers la gauche
    robot_.tournerGauche(VITESSE_ANALYSE, true);
    _delay_ms(100);
    while (!(robot_.lirePins() & D5))
    {
        robot_.tournerGauche(VITESSE_ANALYSE, true);
        _delay_ms(120);
        robot_.eteindre();

        _delay_ms(100); // ✅ Stabilisation du robot

        if ((robot_.lireValeurMoyenne(5) > 150))
        {
            obstacleTrouve = true;
        }

        _delay_ms(100);
    }

    robot_.eteindre();
    _delay_ms(150);
}

void LogiqueRobot::tournerDroiteJusquaProchaineLigne()
{

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
}

void LogiqueRobot::tournerGaucheJusquaProchaineLigne()
{

    robot_.avancer(255);
    _delay_ms(500);
    robot_.tournerGauche(100, true);
    _delay_ms(500);
    while (true)
    {
        if (robot_.lirePins() != 0)
        {
            robot_.eteindre();
            break;
        }
    }
}