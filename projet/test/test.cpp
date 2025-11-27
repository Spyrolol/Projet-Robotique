#include <logique_robot.h>
#include <LED.h>
#include <uart.h>
#include <robot.h>
#include <logiqueLabyrinthe.h>
#include <logique_fourchette.h>
#include <logique_maison.h>
int main()
{

    Robot robot;
    LogiqueRobot logique(robot);
    LogiqueLabyrinthe labyrinthe(logique);
    LogiqueFourchette fourchette(logique);
    LogiqueMaison maison(logique);

    labyrinthe.executer();
}