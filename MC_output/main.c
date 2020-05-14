#define F_CPU 8000000UL
#define RAND_MAX 255
#define TransferSpd 100000
#define True 1
#define False 0
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char timer = False;

ISR(TIMER1_OVF_vect)
{
    timer = True;    
    TCNT1H = (34285>>8);        //delay 1s
    TCNT1L = (34285 & 0xFF);
    
}

int main(void)
{
    unsigned char data;
    //UART initialization
    UBRR0H = (unsigned char)(TransferSpd >> 8);
    UBRR0L = (unsigned char)TransferSpd;
    UCSR0B = (0 << RXEN)|(1 << TXEN);
    UCSR0C = (1 << USBS)|(3 << UCSZ0);
    
    //timer initialization
    sei();
    TIMSK |= (1<<TOIE1); 
    TCCR1B = 0x04;              //F_CPU 256
    TCNT1H = 0xFF;
    TCNT1L = 0xFE;
    
    while (1) 
    {  
        if (timer){            
            data = (unsigned char)rand();
            UDR0 = data;
            timer = False;
        }
        while ( !( UCSR0A & (1<<UDRE)) );       //waiting transfer
    }
}

