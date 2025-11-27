/*

Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: memoire_24
Description: Cette classe s'occupe de configurer et de contrôler la mémoire.
    
*/

#pragma once

#include <avr/io.h>
#include <util/twi.h>
#define F_CPU 8000000
#include <util/delay.h>

class Memoire24CXXX
{
public:

   Memoire24CXXX(); // le constructeur appelle init() decrit plus bas
   ~Memoire24CXXX();

   // procedure d'initialisation appelee par le constructeur
   // Donc, ne pas le refaire a moins de changements en cours
   // d’utilisation.
   void init();
   
   // la procedure init() initialize a zero le "memory bank". 
   // appeler cette methode uniquement si l'adresse doit changer
   static uint8_t choisir_banc(const uint8_t banc);
   
   // deux variantes pour la lecture, celle-ci et la suivante
   // une donnee a la fois
   uint8_t lecture(const uint16_t adresse, uint8_t *donnee);
   // bloc de donnees : longueur doit etre de 127 et moins
   uint8_t lecture(const uint16_t adresse, uint8_t *donnee,
                   const uint8_t longueur);

   // deux variantes pour la l'ecriture egalement:
   // une donnee a la fois
   uint8_t ecriture(const uint16_t adresse, const uint8_t donnee);
   // bloc de donnees : longueur doit etre de 127 et moins
   uint8_t ecriture(const uint16_t adresse, uint8_t *donnee,
                    const uint8_t longueur);

private:
   // pour l'ecriture
   uint8_t ecrire_page(const uint16_t adresse, uint8_t *donnee,
                       const uint8_t longueur);

private:
   // donnees membres
   static uint8_t m_adresse_peripherique;
   const uint8_t TAILLE_PAGE;
};

