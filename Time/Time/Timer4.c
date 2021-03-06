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
volatile unsigned char Time_Stop = 0;
unsigned char timer0Cnt=0;

SIGNAL(INT4_vect)
{
	cli();
	
	if(Time_Stop == 0) Time_Stop = 1;
	else Time_Stop = 0;
	
	sei();
}

SIGNAL(TIMER0_COMP_vect)
{
	cli();
	OCR0 += 72;
	timer0Cnt++;
	
	if(timer0Cnt == 100)
	{
		if(Time_Stop == 0)
		{
		if(time_s >= 9) time_s = 0;
		else time_s++;
		}
		timer0Cnt = 0;
	}
	sei();
}

int main()
{
	DDRA = 0XFF;
	DDRE = 0X00;
	TCCR0 = 0X07;
	OCR0 = 72;
	TIMSK = 0X02;
	TIFR |= 1 <<OCF0;
	
	EICRB = 0x03;
	EIMSK = 0x10;
	EIFR = 0x10;
	
	sei();
	
	while(1)
	{
		PORTA = seg[time_s];
	}
	return 0;
}