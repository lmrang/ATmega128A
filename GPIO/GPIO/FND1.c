/*
 * FND1.c
 *
 * Created: 2022-06-17 오후 4:21:15
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
unsigned char seg[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e};

int main()
{
	DDRA = 0xff;
	while(1)
	{
		for(int i=0;i<16;i++)
		{
			PORTA = seg[i];
			_delay_ms(1000);
			if(i==16) i=0;
		}
	}
	return 0;
}