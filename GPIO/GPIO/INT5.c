/*
 * INT5.c
 *
 * Created: 2022-06-20 오후 1:37:28
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char seg[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e};
int i = 0;
int a = 1;
	
SIGNAL(INT6_vect)
{
	a=1;
}

SIGNAL(INT4_vect)
{
	a=2;
	i=0;
}

int main()
{
	DDRE = 0X00;
	DDRA = 0XFF;
	EIMSK = 1<<INT4 | 1<<INT6;
	EICRB = 1<<ISC41 | 1<<ISC40 | 1<<ISC60 | 1<ISC61;
	sei();
	
	while(1)
	{
		PORTA = seg[i];
		_delay_ms(500);
		
		if(a==1) i++;
		if(i>9) i=0;
	}
	
	return 0;
}