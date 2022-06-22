/*
 * Time.c
 *
 * Created: 2022-06-21 오후 3:30:56
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer0cnt = 0;
SIGNAL(TIMER0_OVF_vect);

int main(void)
{
	DDRC = 0XFF;
	TCCR0=0X07;
	TCNT0 = 180;
	
	TIMSK = 0X01;			//TIMSK |= 1 << TOIE0;
	TIFR |= 1 << TOV0;
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = 180;
	timer0cnt++;
	if(timer0cnt == 100)
	{
		LED_Data++;
		if(LED_Data > 0xff) LED_Data = 0;
		timer0cnt= 0;
	}
	sei();
}

