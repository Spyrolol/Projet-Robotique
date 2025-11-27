/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: interruption


Description: La classe Interruption permet d'initialiser les trois interruptions possibles.
*/
#pragma once
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

class Interruption
{
public:
    Interruption();
    ~Interruption();
    
    void initialisationInt0(const bool frontMontant, const bool frontMontantEtDescendant);
    void initialisationInt1(const bool frontMontant, const bool frontMontantEtDescendant);
    void initialisationInt2(const bool frontMontant, const bool frontMontantEtDescendant);

private:
    
    void initialisationInt(const uint8_t intNum, const bool frontMontant, const bool frontMontantEtDescendant);
};