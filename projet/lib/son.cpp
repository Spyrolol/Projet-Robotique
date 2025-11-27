#include <math.h>
#include "son.h"

#define PRESCALAR 256
#define DELAY_NOTE 1000

Son::Son()
{
    TCCR0A |= ((1 << COM0A0) | (1 << WGM00));
    TCCR0B |= (1 << CS02) | (1 << WGM02);
}
void Son::jouerFrequence(int n)
{
    DDRB |= (1 << PB2) | (1 << PB3);
    if (n >= 45 && n <= 81)
    {
        double frequence = (440 * pow(2, (n - 69) / 12));
        OCR0A = ((F_CPU / (2 * PRESCALAR * frequence)));
    }
}

void Son ::arreterMusique()
{
    DDRB = (0 << PB2) | (0 << PB3);
}

void Son::jouerMusique()
{

    double mozartTheme[] = {60, 62, 64, 65, 67, 69, 71, 72, 72, 71, 69, 67, 65, 64, 62, 60};

    unsigned int i = 0;

    while (i < sizeof(mozartTheme) / sizeof(mozartTheme[0]))
    {
        jouerFrequence(mozartTheme[i]);
        _delay_ms(DELAY_NOTE / 0.5);
        i++;
    }
    arreterMusique();
}