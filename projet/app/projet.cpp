#include <logique_robot.h>
#include <LED.h>
#include <uart.h>
#include <robot.h>
#include <logiqueLabyrinthe.h>
#include <logique_fourchette.h>
#include <logique_maison.h>
#define TOUR_VITESSE 100
#define TOUR_DELAY 50
#define TORQUE_STARTUP 10
enum class NODE
{
    UNKNOWN,
    A,
    J
};

int main()
{
    Robot robot;
    LogiqueRobot logique(robot);
    LogiqueLabyrinthe labyrinthe(logique);
    LogiqueFourchette fourchette(logique);
    LogiqueMaison maison(logique);

    NODE currentNode = NODE::UNKNOWN;

    while (robot.lirePins() != 0 && robot.lirePins() != 31)
    {
        logique.mouvementAutomatique(80);
    }

    if (robot.lirePins() == 0)
        currentNode = NODE::A;

    else
        currentNode = NODE::J;

    switch (currentNode)
    {
    case NODE::UNKNOWN:
    case NODE::A:

        fourchette.pointBC();

        while (!robot.checkIntersection())
        {
            logique.mouvementAutomatique(90);
        }
        logique.tournerDroiteJusquaProchaineLigne();

        maison.runMaison();

        while (!robot.checkIntersection())
        {
            logique.mouvementAutomatique(90);
        }
        logique.tournerDroiteJusquaProchaineLigne();
        while (robot.lirePins() != 31)
        {
            logique.mouvementAutomatique(80);
        }

        labyrinthe.executer();

        while (!robot.checkIntersection())
        {
            logique.mouvementAutomatique(90);
        }
    
        break;

    case NODE::J:

        labyrinthe.executer();

        while (!robot.checkIntersection())
        {
            logique.mouvementAutomatique(90);
        }
        logique.tournerDroiteJusquaProchaineLigne();

        fourchette.pointBC();

        while (!robot.checkIntersection())
        {
            logique.mouvementAutomatique(90);
        }
        logique.tournerDroiteJusquaProchaineLigne();

        maison.runMaison();

        while (!robot.checkIntersection())
        {
            logique.mouvementAutomatique(90);
        }

        break;
    }
    //Logique pour se recentrer a la fin
    robot.avancer(160);
    _delay_ms(1200);
    robot.tournerDroite(170, true);
    _delay_ms(400);

    while (robot.lirePins() == 0)
    {
        robot.tournerDroite(255, true);
        _delay_ms(TORQUE_STARTUP);
        robot.tournerDroite(TOUR_VITESSE, true);
        _delay_ms(TOUR_DELAY);
    }

    robot.eteindre();
    _delay_ms(400);
    robot.alternerDEL_2HZ();
}
