/*
 * led2.c
 *
 * Created: 2022-06-17 오후 1:54:31
 *  Author: PKNU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0XFF;
	//unsigned char shift = 0x80;
	unsigned char led[] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0XFB, 0XFD, 0XFE};
	unsigned char seg[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6};
	
	while(1)
	{
		for(int i=0;i<8;i++)
		{
			PORTA = seg[i];
			_delay_ms(500);
			if(i==8) i=0;
		}
		
		/*PORTA = shift;
		_delay_ms(50);
		
		if(PORTA==0x00) shift=0x80;
		else shift = shift>>1;*/
	}
	return 0;
}