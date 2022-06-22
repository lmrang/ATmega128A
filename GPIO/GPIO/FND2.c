/*
 * FND2.c
 *
 * Created: 2022-06-17 오후 4:26:37
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
unsigned char seg[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e};
	
int main()
{
	DDRD = 0X00;
	DDRA = 0XFF;
	int i = 0;
	while(1)
	{
		
		if(PIND == 0x01) 
		{
			_delay_ms(10);
			i = 1;
		}
		else if(PIND == 0x02)
		{
			_delay_ms(10);
			i = 2;
		}
		else if(PIND == 0x04)
		{
			_delay_ms(10);
			i = 3;
		}
		else if(PIND == 0x08)
		{
			_delay_ms(10);
			i = 4;
		}

		PORTA = seg[i];
	}
	return 0;
}