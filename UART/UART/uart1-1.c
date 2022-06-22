/*
 * usart.c
 *
 * Created: 2013-09-11 오전 11:21:11
 *  Author: Administrator
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

void init_USART0(void)
{
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0A = 0x00;
	//UCSR0C = (1<<UPM01)|(1<<UCSZ01)|(1<<UCSZ00);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0H = 0x00;
	UBRR0L = 3;
	//sei();
}

void putch_USART0(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}
void puts_USART0(char *str)
{
	while(*str != 0){
		putch_USART0(*str);
		str++;
	}
}
unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data; 
}
int main(void)
{
	//char array[] = "Embedded Hong kil-dong\r\n";
	char array[20];
	init_USART0();
	char data;
	DDRC = 0xFF;
    while(1)
    {
		//putch_USART0(getch());
        //puts_USART0(array);
		data = getch();
		if(data == '1') PORTC = 0x01;
		_delay_ms(500);
    }
}
