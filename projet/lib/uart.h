/*
Nom: Benziane Younes (2382041), Bouguerra Billel(2370115), Cipcigan Raul (2262352), El Yamani Zakaria(2373873)
Groupe: 04
Projet final: UART
Description: Permet de configurer et de contrôler une communication UART.Supporte la transmission et la réception de données.
*/
#pragma once
#include <avr/io.h>
#include <stdint.h>
#include <avr/eeprom.h>
#include "memoire_24.h"

class UART
{
public:
    UART();
    ~UART();
    void initialiseUART();
    void lireDataParByte(unsigned char* data, uint8_t length, Memoire24CXXX memory);
    void transmettreUART(unsigned char data);
    unsigned char recevoirUART(void);
    void ecrireString(const char* data);
protected:
    static constexpr uint8_t VALEUR_UBRR = 0xCF;
};