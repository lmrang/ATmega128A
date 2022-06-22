/*
 * Timer16.c
 *
 * Created: 2022-06-22 오전 10:15:10
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;

SIGNAL(TIMER1_OVF_vect)
{
	cli();
	TCNT1 = 36736;
	
	LED_Data++;
	if(LED_Data > 0xff) LED_Data = 0;
		
	sei();
}

int main(void)
{
	DDRC = 0xff;
	
	TCCR1A = 0X00;
	TCCR1B = (1 << CS12);
	
	TCNT1 = 36736;				//65536 - (7372800 / 255) = 36736
	TIMSK = (1 << TOIE1);
	//TIFR |= 1 <<TOV1;
	
	sei();
    while (1) 
    {
		PORTC = LED_Data;
    }
	return 0;
}

