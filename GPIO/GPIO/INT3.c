/*
 * 응용2.c
 *
 * Created: 2022-06-20 오후 12:25:28
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int stop = 1;

SIGNAL(INT4_vect)
{
	stop = 1;
}

SIGNAL(INT5_vect)
{
	stop = 2;
}

int main()
{
	unsigned char led;
	led = 0x01;
	DDRE = 0X00;
	DDRA = 0XFF;
	EIMSK = 1<<INT4 | 1<<INT5;
	EICRB = 1<<ISC41 | 1<<ISC40 | 1<<ISC50 | 1<<ISC51;
	sei();
	
	while(1)
	{
		PORTA = led;
		_delay_ms(500);
		if(stop == 2)
		{
			if(led == 0x80) led = 0x01;
			else led = (led<<1);
		}
		else if(stop == 1)
		{
			if(led == 0x01) led = 0x80;
			else led = (led >> 1);
		}
	}
	
	return 0;
}
