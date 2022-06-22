/*
 * Timer3.c
 *
 * Created: 2022-06-21 오후 4:14:12
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char seg[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e};

volatile unsigned char time_s=0;
unsigned char timer0Cnt=0;

SIGNAL(TIMER0_COMP_vect)
{
	cli();
	OCR0 += 72;
	timer0Cnt++;
	
	if(timer0Cnt == 100)
	{
		
		if(time_s >= 9) time_s = 0;
		else time_s++;
		timer0Cnt = 0;
	}
}

int main()
{
	DDRA = 0XFF;
	TCCR0 = 0X07;
	OCR0 = 72;
	TIMSK = 0X02;
	TIFR |= 1 <<OCF0;
	sei();
	
	while(1)
	{
		PORTA = seg[time_s];
	}
	return 0;
}