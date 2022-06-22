/*
 * UART1.c
 *
 * Created: 2022-06-21 오전 10:47:54
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0x20)==0);
	UDR0 =data;
	UCSR0A |= 0X20;
}

int main()
{
	unsigned int i=0;
	int TX=0;
	int a=0;
	DDRE = 0xfe;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0X00;
	UBRR0L = 3;
	
	DDRA=0x00;
	char text[30];
	while(1)
	{
		if(TX==1)
		{
			sprintf(text, "Input Switch : %d \r\n", a);
			while(text[i] != '\0') putch(text[i++]);
			TX=0;
			_delay_ms(500);
		}
		
		if(PINA==0X01)
		{
			i=0;
			TX=1;
			a=0;
		}
		
		if(PINA==0X02)
		{
			i=0;
			TX=1;
			a=1;
		}
	}
	
	return 0;
}
