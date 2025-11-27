#include "Moteur.h"
#define msPourRotationDroite 500
#define msPourRotationGauche 550

// PD6 / PD7 : DIRECTION (1 = RECULER, 0 = AVANCER)
// PD4 / PD5 : ENABLE (1 = ON, 0 = OFF)

// P4 / P6 : ROUE DROITE
// P5 / P7 : ROUE GAUCHE

Moteur::Moteur()
{
    DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
    initialisation();
}

void Moteur::initialisation()
{
    // TCNT1 = 0;

    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << CS11);
    TCCR1C = 0;
    // TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);
}

void Moteur::avancer(uint8_t dutyCycle)
{
    OCR1A = dutyCycle;
    OCR1B = dutyCycle;
    PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD7);
}

void Moteur::reculer(uint8_t dutyCycle)
{
    OCR1A = dutyCycle;
    OCR1B = dutyCycle;
    PORTD |= (1 << PD6);
    PORTD |= (1 << PD7);
}

void Moteur::eteindre()
{
    OCR1A = 0;
    OCR1B = 0;
    /* PORTD &= ~(1 << PD6);
    PORTD &= ~(1 << PD7);
    PORTD &= ~(1 << PORTD4);
    PORTD &= ~(1 << PORTD5); */
}

void Moteur::tournerDroite90()
{
    OCR1A = 1;
    OCR1B = 1;

    PORTD |= (1 << PD6);
    PORTD |= (1 << PD7);

    _delay_ms(msPourRotationGauche);

    eteindre();
}

void Moteur::tournerGauche90()
{
    OCR1A = 1;
    OCR1B = 1;

    PORTD &= ~(1 << PD7);
    PORTD |= (1 << PD6);

    _delay_ms(msPourRotationDroite);

    eteindre();
}

void Moteur::tournerGauche(uint8_t dutyCycle, bool surPlace)
{
    OCR1A = dutyCycle;
    if (surPlace)
    {
        OCR1B = dutyCycle;
    }
    else
    {
        OCR1B = dutyCycle / 2;
    }

    PORTD &= ~(1 << PD7);
    if (surPlace)
    {
        PORTD |= (1 << PD6);
    }
    else
    {
        PORTD &= ~(1 << PD6);
    }
}

void Moteur::tournerDroite(uint8_t dutyCycle, bool surPlace)
{
    if (surPlace)
    {
        OCR1A = dutyCycle;
    }
    else
    {
        OCR1A = dutyCycle / 2;
    }
    OCR1B = dutyCycle;

    PORTD &= ~(1 << PD6);
    if (surPlace)
    {
        PORTD |= (1 << PD7);
    }
    else
    {
        PORTD &= ~(1 << PD7);
    }
}

void Moteur::tourGaucheSharp(uint8_t dutyCycle) {
    OCR1A = dutyCycle;
    OCR1B = 0;

    PORTD &= ~(1 << PD7);
}

void Moteur::tourDroiteSharp(uint8_t dutyCycle) {
    OCR1A = 0;
    OCR1B = dutyCycle;

    PORTD &= ~(1 << PD6);
}