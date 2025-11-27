#include "uart.h"
#include "memoire_24.h"
#include <string.h>

UART::UART()
{
    initialiseUART();
}

UART::~UART() = default;

void UART::initialiseUART()
{
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (0<<USBS0)|(1 <<UCSZ00)|(1<<UCSZ01);
    // [USBS0] : Set le nombre de stop bits, [UCSZ00 & UCSZ01] : Set le nombres de bits
}

void UART::transmettreUART(unsigned char data)
{
    // On attends que le buffer est vide
    while (!(UCSR0A & (1 << UDRE0))) {}
    
    // Quand le buffer est vide, on met le data dans UDR0
    UDR0 = data;
}

unsigned char UART::recevoirUART(void) {
    
    while (!(UCSR0A & (1 << RXC0)));

    return UDR0;
} 

void UART::lireDataParByte(unsigned char* data, uint8_t length, Memoire24CXXX memory)
{
    for (uint8_t i = 0; i < length; i++)
    {
        memory.lecture(0x00 + i, &data[i]);
        transmettreUART(data[i]);
    }
}

void UART::ecrireString(const char* data) 
{
    for (size_t i = 0; i < strlen(data); i++) {
        transmettreUART(data[i]);
    }
}