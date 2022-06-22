/*
 * INT2.c
 *
 * Created: 2022-06-20 오전 10:39:34
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int stop = 1;

SIGNAL(INT4_vect)
{
  stop *= (-1);
}

int main()
{
	unsigned char led;
	led = 0x01;
	DDRE = 0X00;
	DDRA = 0XFF;
	EIMSK = 1<<INT4;
	EICRB = 1<<ISC41 | 1<<ISC40;
	sei();
	
	while(1)
	{
		if(stop > 0)
		{
			PORTA = led;
			_delay_ms(500);
			if(led == 0x80) led = 0x01;
			else led = (led<<1);
		}
		else PORTA = led;
	}
	
	return 0;
}