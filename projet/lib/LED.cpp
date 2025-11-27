#include "LED.h"

Led::Led( volatile uint8_t *portx,  volatile uint8_t *ddrx, const uint8_t rougePin, const uint8_t vertPin)
    : portx_(portx), rougePin_(rougePin), vertPin_(vertPin)
{
    *ddrx |= (1 << rougePin_);
    *ddrx |= (1 << vertPin_);
}

void Led ::allumerRouge()
{
    *portx_ &= ~(1 << vertPin_);
    *portx_ |= (1 << rougePin_);
}

void Led ::allumerVert()
{
    *portx_ &= ~(1 << rougePin_);
    *portx_ |= (1 << vertPin_);
}

void Led ::allumerAmbre()
{
    
    *portx_ &= ~(1 << vertPin_);
    *portx_ |= (1 << rougePin_);
    _delay_ms(ROUGE_AMBRE_DELAI_MS);

    *portx_ &= ~(1 << rougePin_);
    *portx_ |= (1 << vertPin_);
    _delay_ms(VERT_AMBRE_DELAI_MS);
}

void Led ::eteindreLumiere()
{
    *portx_ &= ~(1 << rougePin_);
    *portx_ &= ~(1 << vertPin_);
}

void Led::alternerDEL_2HZ()
{
    while (true)
    {
        allumerRouge();
        
        _delay_ms(250);
        eteindreLumiere();
        allumerVert();
         _delay_ms(250);
        eteindreLumiere();
      
    }
}

