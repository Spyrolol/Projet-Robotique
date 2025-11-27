#include "minuterie.h"

Minuterie::Minuterie(uint8_t numeroMinuterie)
{
    // numero minuterie doit etre valide
    if (numeroMinuterie > 2 || numeroMinuterie < 0)
    {
        return;
    }
    numeroMinuterie_ = numeroMinuterie;
}

void Minuterie::compareA(const uint16_t duree)
{
    switch (numeroMinuterie_)
    {
    case 0:
        OCR0A = duree;           // Definit la valeur compare
        TIMSK0 |= (1 << OCIE0A); // Active interuption timer
        break;
    case 1:
        OCR1A = duree;
        TIMSK1 |= (1 << OCIE1A);
        break;
    case 2:
        OCR2A = duree;
        TIMSK2 |= (1 << OCIE2A);
        break;
    }

    sei();
}

void Minuterie::compareB(const uint16_t duree)
{

    switch (numeroMinuterie_)
    {
    case 0:
        OCR0B = duree;
        TIMSK0 |= (1 << OCIE0B);
        break;
    case 1:
        OCR1B = duree;
        TIMSK1 |= (1 << OCIE1B);
        break;
    case 2:
        OCR2B = duree;
        TIMSK2 |= (1 << OCIE2B);
        break;
    }

    sei();
}

void Minuterie::modeCTC()
{
    TCCR2A = 0;

    switch (numeroMinuterie_)
    {
    case 0:
        // Pour Timer 0, mode CTC

        TCCR0A |= (1 << COM0A0) | (1 << COM0B0);
        TCCR0B |= (1 << WGM02);
        break;
    case 1:
        // Pour Timer 1, mode CTC

        TCCR1A |= (1 << COM1A0) | (1 << COM1B0);
        TCCR1B |= (1 << WGM12);
        break;
    case 2:
        // Pour Timer 2, mode CTC

        TCCR2A |= (1 << COM2A0) | (1 << COM2B0);
        TCCR2B |= (1 << WGM22);
        break;
    }
}


void Minuterie::modeNormal()
{
    switch (numeroMinuterie_)
    {
    case 0:
        // Pour Timer 0, mode Normal

        TCCR0A &= ~(1 << WGM00) | (1 << WGM01);
        TCCR0A |= (1 << COM0A0) | (1 << COM0B0);
        break;
    case 1:
        // Pour Timer 1, mode Normal

        TCCR1B &= ~((1 << WGM12) | (1 << WGM13));
        TCCR1A &= ~(1 << WGM10) | (1 << WGM11);

        TCCR1A |= (1 << COM1A0) | (1 << COM1B0);
        break;
    case 2:
        // Pour Timer 2, mode Normal

        
        TCCR2A &= ~(1 << WGM20) | (1 << WGM21);
        TCCR2A |= (1 << COM2A0) | (1 << COM2B0);
        break;
    }
}

void Minuterie::modeRapidePWM()
{
    switch (numeroMinuterie_)
    {
    case 0:
        // Pour Timer 0, Fast PWM
        TCCR0A |= (1 << WGM00) | (1 << WGM01);

        TCCR0A |= (1 << COM0A0);
        break;
    case 1:
        // Pour Timer 1, Fast PWM 16-bit ,cest pour ca on utilise WGMn2 et WGMn3
        TCCR1B |= (1 << WGM12) | (1 << WGM13);
        TCCR1A |= (1 << WGM10) | (1 << WGM11);
        TCCR1A |= (1 << COM1A0);
        break;
    case 2:
        // Pour Timer 2, Fast PWM
        TCCR2A |= (1 << WGM20) | (1 << WGM21);

        TCCR2A |= (1 << COM2A0);
        break;
    }
}

void Minuterie::configurerPrescaler(prescaler prescal)
{
    switch (numeroMinuterie_)
    {
    case 0:
        // Effacer tous les bits du prédiviseur
        TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));

        // Définir les bits appropriés

        switch (prescal)
        {
        case prescaler::PRESCALER_1:
            TCCR0B |= (1 << CS00);
            break;
        case prescaler::PRESCALER_8:
            TCCR0B |= (1 << CS01);
            break;
        case prescaler::PRESCALER_64:
            TCCR0B |= (1 << CS00) | (1 << CS01);
            break;
        case prescaler::PRESCALER_256:
            TCCR0B |= (1 << CS02);
            break;
        case prescaler::PRESCALER_1024:
            TCCR0B |= (1 << CS00) | (1 << CS02);
            break;
        default:
            break;
        }
        break;
    case 1:
        // Effacer tous les bits du prédiviseur
        TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));

        // Définir les bits appropriés en fonction de la valeur de prescaler
        switch (prescal)
        {
        case prescaler::PRESCALER_1:
            TCCR1B |= (1 << CS10);
            break;
        case prescaler::PRESCALER_8:
            TCCR1B |= (1 << CS11);
            break;
        case prescaler::PRESCALER_64:
            TCCR1B |= (1 << CS10) | (1 << CS11);
            break;
        case prescaler::PRESCALER_256:
            TCCR1B |= (1 << CS12);
            break;
        case prescaler::PRESCALER_1024:
            TCCR1B |= (1 << CS10) | (1 << CS12);
            break;
        default:
            break;
        }
        break;

    case 2:
        // Effacer tous les bits du prédiviseur
        TCCR2B &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));

        // Définir les bits appropriés
        switch (prescal)
        {
        case prescaler::PRESCALER_1:
            TCCR2B |= (1 << CS20);
            break;
        case prescaler::PRESCALER_8:
            TCCR2B |= (1 << CS21);
            break;
        case prescaler::PRESCALER_64:
            TCCR2B |= (1 << CS20) | (1 << CS21);
            break;
        case prescaler::PRESCALER_256:
            TCCR2B |= (1 << CS22);
            break;
        case prescaler::PRESCALER_1024:
            TCCR2B |= (1 << CS20) | (1 << CS22);
            break;
        default:
            break;
        }
        break;
    }
}

void Minuterie::arreterMinuterie()
{
    switch (numeroMinuterie_)
    {
    case 0:
        TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02)); // arrête timer en mettant le prescaler à 0
        TIMSK0 &= ~((1 << OCIE0A) | (1 << OCIE0B));
        TCNT0 = 0;

        break;
    case 1:
        TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12)); // arrête timer en mettant le prescaler à 0
        TIMSK1 &= ~((1 << OCIE1A) | (1 << OCIE1B));           // Désactive les interruptions
        TCNT1 = 0;                                            // Remet le compteur à 0
        break;
    case 2:
        TCCR2B &= ~((1 << CS20) | (1 << CS21) | (1 << CS22)); // arrête timer en mettant le prescaler à 0
        TIMSK2 &= ~((1 << OCIE2A) | (1 << OCIE2B));
        TCNT2 = 0;

        break;
    }
}

void Minuterie::demarrerMinuterie()
{
    switch (numeroMinuterie_)
    {
    case 0:
    {
        uint8_t prescalerTccr0b = TCCR0B & ~((1 << CS00) | (1 << CS01) | (1 << CS02));
        // Reaplique la valeur qui etait la du prescaler
        TCCR0B = prescalerTccr0b | ((1 << CS01));
        break;
    }
    case 1:
    {
        uint8_t prescalerTccr1b = TCCR1B & ~((1 << CS10) | (1 << CS11) | (1 << CS12));
        // Reaplique la valeur qui etait la
        TCCR1B = prescalerTccr1b | ((1 << CS11));
        break;
    }
    case 2:
    {
        uint8_t prescalerTccr2b = TCCR0B & ~((1 << CS20) | (1 << CS21) | (1 << CS22));
        // Reaplique la valeur qui etait la
        TCCR2B = prescalerTccr2b | ((1 << CS21));
        break;
    }
    }
}

Minuterie::~Minuterie()
{
    arreterMinuterie();
}