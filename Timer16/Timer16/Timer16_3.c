/*
 * Timer16_3.c
 *
 * Created: 2022-06-22 오전 11:43:43
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char seg[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e};

unsigned int i=0;

SIGNAL(TIMER1_COMPA_vect)
{
	cli();
	
	OCR1A += 7200;
	if(i>=9) i=0;
	else i++;
	
	sei();
}

int main()
{
	DDRE = 0xFF;
	
	TCCR1A = 0x00;
	TCCR1B = (1<<CS12) | (1<<CS10);
	
	OCR1A = 7200;			// 7372800 / 1024 = 7200
	TIMSK = (1<<OCIE1A);
	sei();
	
	while(1)
	{
		PORTE = seg[i];
	}
	return 0;
}