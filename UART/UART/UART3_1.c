/*
 * UART3_1.c
 *
 * Created: 2022-06-21 오후 2:05:38
 *  Author: PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <stdio.h>

unsigned char seg[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6, 0xEE, 0x3E, 0x9C, 0x7A, 0x9E};
	
void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

int main()
{
	unsigned char rx;
	DDRB = 0xFF;
	DDRE = 0xFE;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	while(1)
	{
		rx = getch();
		putch(rx);
		//PORTB = seg[0];
		//if((rx>= 0x30) && (rx <= 0x39))
		//{
		//	PORTB = seg[rx - 0x30];
		//}
	}
	return 0;
}
