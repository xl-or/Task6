#define F_CPU 8000000UL
#define TransferSpd 100000
#include <avr/io.h>


int main(void)
{
    unsigned char number[16] = {
        0x3F,           //0
        0x06,           //1
        0x5B,           //2
        0x4F,           //3
        0x66,           //4
        0x6D,           //5
        0x7D,           //6
        0x07,           //7
        0x7F,           //8
        0x6F,           //9
        0x77,           //(10) A
        0x7F,           //(11) B == 8?
        0x39,           //(12) C
        0x3F,           //(13) D == 0?
        0x79,           //(14) E
        0x71            //(15) F
    };
    DDRA = 0xFF;
    DDRB = 0xFF;
    unsigned char data;
    UBRR0H = (unsigned char)(TransferSpd >> 8);
    UBRR0L = (unsigned char)TransferSpd;
    UCSR0B = (1 << RXEN)|(0 << TXEN);
    UCSR0C = (1 << USBS)|(3 << UCSZ0);
    
    
    while (1)
    {
        while ( !(UCSR0A & (1<<RXC)) );
        data = UDR0;
        PORTA = number[data / 16];
        PORTB = number[data % 16];
    }
}

