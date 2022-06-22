/*
 * UART.c
 *
 * Created: 2022-06-21 오전 9:35:17
 * Author : PKNU
 */ 

#include <avr/io.h>
#define F_CPU 7432800UL

void putch(unsigned char data)
{
	while((UCSR0A & 0x20)==0);
	UDR0 =data;
	UCSR0A |= 0X20;
}

int main(void)
{
	unsigned char text[] = "Hello! world!! \r\n";
	unsigned char i=0;
	
	DDRE = 0xfe;		//rx(입력 0), tx(출력 1)
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0X00;
	UBRR0L = 3;
	
    while (text[i]!='\0') 
    {
		putch(text[i++]);
    }
}


