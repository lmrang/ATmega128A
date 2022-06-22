/*
 * UART3.c
 *
 * Created: 2022-06-21 오후 12:02:10
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

unsigned char seg[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e};

void puts_USART0(char *str)
{
	while(*str!=0)
	{
		putch(*str);
		str++;
	}
}

void putch(unsigned char data)
{
	while((UCSR0A & 0x20)==0);
	UDR0 =data;
	UCSR0A |= 0X20;
}

unsigned char getch() 
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0X80;
	return data;
}

int main()
{
	unsigned char RX;
	DDRC = 0xff;
	//DDRE = 0xfe;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0X00;
	UBRR0L = 3;
	
	//PORTB = seg[0];
	while(1)
	{
		RX=getch();
		if(RX == '1'){
			PORTC = 0x01;
		}
		//PORTC = seg[0];
		//if((RX >= 0x30) && (RX <= 0x39))
		//{
			//PORTC = seg[RX - 0x30];
		//}
		
	}
	
	return 0;
}