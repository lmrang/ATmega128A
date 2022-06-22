/*
 * UART2.c
 *
 * Created: 2022-06-21 오전 11:35:25
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

unsigned char getch() {
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0X80;
	return data;
}

int main()
{
	DDRE = 0xfe;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0X00;
	UBRR0L = 3;
	
	unsigned char text[] = "\r\nWelcome! edgeiLAB\r\n USART0 TEST Program.\r\n";
	unsigned char echo[] = "ECHO >> ";
	unsigned char i=0;
	
	while(text[i]!='\0') putch(text[i++]);
	
	i=0;
	
	while(echo[i] != '\0') putch(echo[i++]);
	while(1) {
		putch(getch());
	}
	
	return 0;
}