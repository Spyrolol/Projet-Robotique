#include "Interruption.h"

void Interruption::initialisationInt(const uint8_t numeroInterruption, const bool frontMontant, const bool frontMontantEtDescendant)
{
    if (frontMontant && frontMontantEtDescendant)
    {
        return; // Quitte la methode
    }

    cli();
    EIMSK |= (1 << numeroInterruption);

    
    EICRA &= ~(0b11 << (numeroInterruption * 2)); // Efface les 2 bits correspondants

    if (frontMontantEtDescendant)
    {
        EICRA |= (1 << (numeroInterruption * 2));
    }
    else
    {
        if (frontMontant)
        {
            EICRA |= (1 << ((numeroInterruption * 2) + 1)) | (1 << (numeroInterruption * 2));
        }
        else
        {
            EICRA |= (1 << ((numeroInterruption * 2) + 1));
        }
    }
    sei();
}

void Interruption::initialisationInt0(const bool frontMontant, const bool frontMontantEtDescendant)
{
    initialisationInt(INT0, frontMontant, frontMontantEtDescendant);
}

void Interruption::initialisationInt1(const bool frontMontant, const bool frontMontantEtDescendant)
{
    initialisationInt(INT1, frontMontant, frontMontantEtDescendant);
}

void Interruption::initialisationInt2(const bool frontMontant, const bool frontMontantEtDescendant)
{
    initialisationInt(INT2, frontMontant, frontMontantEtDescendant);
}