/*
 
Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873) 
Groupe: 04
Projet final: debug

Description: Ces fichiers permettent d'utiliser PRINT_DEBUG() pour appeler printDebug et écrire un message de debug au RS232.
*/
#pragma once

#ifdef DEBUG
void printDebug(char data[]);
#define PRINT_DEBUG(x) printDebug(x)

#else
#define PRINT_DEBUG(x) while (0)

#endif