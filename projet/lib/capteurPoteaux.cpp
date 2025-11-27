#include "capteurPoteaux.h"
#define BITSHIFT 2 // 👈 ici, visible pour tout le projet
/*
110=50cm
200=32cm
150=39cm
*/
capteurPoteaux::capteurPoteaux(uint8_t port) : port_{port} {}
capteurPoteaux::~capteurPoteaux() {}

uint16_t capteurPoteaux::lireValeurBrute()
{
    return convertisseur_.lecture(port_);
}

uint16_t capteurPoteaux::lireValeurMoyenne(uint8_t nbMesures)
{
    uint32_t somme = 0;
    for (uint8_t i = 0; i < nbMesures; ++i)
    {
        somme += lireValeurBrute();
        _delay_ms(5);
    }
    return somme / nbMesures;
}

bool capteurPoteaux::detecter(uint8_t distanceSeuil)
{
    uint16_t valeurBrute = lireValeurBrute();

    // Convertir en 8 bits si nécessaire (si ADC est sur 10 bits)
    uint16_t valeur8Bits = valeurBrute >> BITSHIFT; // BITSHIFT = 2 ou 4 selon ta config
    uint8_t distanceCalculee = convertirEnDistance(valeur8Bits);

    if (distanceCalculee < 10)
    {
        return false; // Trop proche = instable
    }

    return (distanceCalculee <= distanceSeuil);
}

// Conversion de la valeur ADC en cm selon la courbe du capteur IR Sharp
uint8_t capteurPoteaux::convertirEnDistance(uint16_t valeur)
{
    /*if (valeur <= 30)
        return 255; // Trop faible = rien détecté*/

    // float distance = 1 / (0.05 * valeur);
    float distance = 3000.0 / (valeur - 30); // calibration à ajuster

    /*if (distance > 255.0)
        return 255;*/

    return static_cast<uint8_t>(distance);
}

uint8_t capteurPoteaux::lireDistance()
{
    uint16_t moyenne = lireValeurMoyenne();
    return convertirEnDistance(moyenne);
}

bool capteurPoteaux::detecterObjet(uint8_t distance_seuil)
{

    uint8_t distance = lireDistance();

    if (distance < 10)
        return false;

    return (distance <= distance_seuil);
}

// Nouvelle méthode basée sur la valeur brute de l'ADC
bool capteurPoteaux::objetEstPresent()
{
    uint16_t adc = lireValeurBrute();
    return (adc >= 200 && adc <= 400);
}
