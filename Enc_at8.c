/*
 * Enc_at8.c
 *
 * Created: 4/26/2014 4:06:56 PM
 *  Author: YateenKedare
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

void Usart_init(void)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);
	UCSRA |= (1<<U2X);
	UBRRH = 0;
	UBRRL = 12;
	DDRD &= ~(1<<PD0);
	DDRD |= (1<<PD1);
	
	PORTD &= ~(1<<PD0);
	PORTD |= (1<<PD1);
}

uint8_t UartReceive(void)
{
	while( !(UCSRA & (1<<RXC)) );
	return UDR;
}

void UartTransmit(uint8_t data)
{
	while ( !( UCSRA & (1<<UDRE)) );
	UDR = data;
}

void Timer_init(void)
{
	TCCR1B = 0x07;
	DDRD &= ~(1<<PD5);
	PORTD |= (1<<PD5);
}

int main(void)
{
	int c;
	Usart_init();
	Timer_init();
    while(1)
    {
        c = UartReceive();
		switch(c)
		{
			case 10:
				UartTransmit(TCNT1L);
				UartTransmit(TCNT1H);
			break;
			
			case 30:
				TCNT1 = 0;
			break;
		}
    }
}