/*
 * UART.c
 *
 * Created: 2022-06-24 오후 12:12:22
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

void init_USART0(void)
{
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0A = 0x00;
	//UCSR0C = (1<<UPM01)|(1<<UCSZ01)|(1<<UCSZ00);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0H = 0x00;
	UBRR0L = 3;
}

void puts_USART0(char *str)
{
	while(*str != 0){
		putch_USART0(*str);
		str++;
	}
}

void putch_USART0(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}