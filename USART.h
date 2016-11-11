
void Timer_init()
{
	TCCR1B = 0x07;
	DDRD &= ~(1<<6);
	PORTD |= (1<<6);
}

void Usart_init(void)
{
	UCSR1B |= (1 << RXEN1) | (1 << TXEN1);
	UCSR1C |= (1 << UCSZ11) | (1 << UCSZ01);
	UCSR1A |= (1<<U2X1);
	UBRR1H = 0;
	UBRR1L = 191;
	DDRD &= ~(1<<PD2);
	DDRD |= (1<<PD3);	
	
	PORTD &= ~(1<<PD2);
	PORTD |= (1<<PD3);
}

uint8_t UartReceive(void)
{
	while( !(UCSR1A & (1<<RXC1)) );
	return UDR1;
}

void UartTransmit(uint8_t data)
{
	while ( !( UCSR1A & (1<<UDRE1)) );
	UCSR1B &= ~(1<<TXB81);
	if ( data & 0x0100 )
		UCSR1B |= (1<<TXB81);
	UDR1 = data;
}

void UartFlush( void )
{
	unsigned char dummy;
	while ( UCSR1A & (1<<RXC1) ) dummy = UDR1;
}