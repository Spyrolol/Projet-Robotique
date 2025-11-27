
#include "bouton.h"

Bouton::Bouton() 
          // Initialisation de l'objet Led avec les ports et pins
    {
        // Initialisation des registres pour les pins
        DDRD &= ~(1 << PIN2);  // Configure le pin D2 en entrÃ©e (bouton)
        DDRB &= ~((1 << PB1) |(1 << PB0));
    }

bool Bouton::boutonAppuyer(){

    if (!(PIND & (1 << PIN2))) {
		return false;
	}
    _delay_ms(DELAY_MS);
    if ( PIND & (1 << PIN2)) {
        return true;
    }
    else{
        return false;
    }
}
bool Bouton::boutonBreadboardAppuye(){

    if ((PINB & (1 << PB0))) {
		return false;
	} else {
        return true;
    }
}