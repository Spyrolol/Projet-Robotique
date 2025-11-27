#include "capteur_ligne.h"
#include "uart.h"

#define bitShift1 0
#define bitShift2 1
#define bitShift3 2
#define bitShift4 3
#define bitShift5 4

#define D1 0x01 // 00001
#define D2 0x02 // 00010
#define D3 0x04 // 00100
#define D4 0x08 // 01000
#define D5 0x10 // 10000

CapteurLigne::CapteurLigne()
{
    // CapteurLigne(&PORTA, &DDRA, PA6, PA3, PA5, PA4, PA2)
    DDRA &= ~(1 << PA6);
    DDRA &= ~(1 << PA3);
    DDRA &= ~(1 << PA5);
    DDRA &= ~(1 << PA4);
    DDRA &= ~(1 << PA2);
    // Active les résistances pull-up
    PORTA |= (1 << PA6) | (1 << PA3) |
             (1 << PA5) | (1 << PA4) | (1 << PA2);
}

uint8_t CapteurLigne::lirePins()
{
    bool premierBit = PINA & (1 << PA6);
    bool deuxiemeBit = PINA & (1 << PA3);
    bool troisiemeBit = PINA & (1 << PA5);
    bool quatriemeBit = PINA & (1 << PA4);
    bool cinquiemeBit = PINA & (1 << PA2);

    return (premierBit << bitShift1) | (deuxiemeBit << bitShift2) | (troisiemeBit << bitShift3) | (quatriemeBit << bitShift4) | (cinquiemeBit << bitShift5);
}

bool CapteurLigne::checkIntersection()
{
    bool premierBit = PINA & (1 << PA6);
    bool deuxiemeBit = PINA & (1 << PA3);
    bool troisiemeBit = PINA & (1 << PA5);
    bool quatriemeBit = PINA & (1 << PA4);
    bool cinquiemeBit = PINA & (1 << PA2);

    int nBit = int(premierBit) + int(deuxiemeBit) + int(troisiemeBit) + int(quatriemeBit) + int(cinquiemeBit);
    if (nBit >= 4)
    {
        return true;
    }
    return false;
}

bool CapteurLigne::checkIntersectionDirectionelle(bool gauche) {
    switch (gauche) {
        case true:
            return (lirePins() & (D1) && lirePins() & (D2) && lirePins() & (D3));

        case false:
            return (lirePins() & (D4) && lirePins() & (D5) && lirePins() & (D3));
    }
}