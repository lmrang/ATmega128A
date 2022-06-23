/*
 * PIEZO_KEYBOARD.c
 *
 * Created: 2022-06-23 오전 10:56:01
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
volatile unsigned char soung_flag = 1;

void U_init()
{
	UCSR0A = 0x00;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0H = 0x00;
	UBRR0L = 3;		//115200
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

void putch(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

int main()
{
	DDRE = 0xff;
	DDRA = 0xff;
	U_init();
	
	char input;
	
	TCCR3A = 0x00;
	TCCR3B = (1<<WGM33) | (1<<WGM32) | (1<<CS30);				// CTC모드, 프리스케일링 없음
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	while(1)
	{
		input = getch();
		
		if((input>0x30) && (input<0x39))
		{
			ICR3 = 7372800 / DoReMi[input-0x30] /4;
			TCCR3A = 0x40;					//PE3(OC3A)으로 출력
			_delay_ms(200);
			TCCR3A=0X00;					//출력 없음
		}
		
		//if(input == '1')
		//{
			//PORTA = 0x01;
			//ICR3 = 7372800 / DoReMi[0] /5;
			//TCCR3A = 0x40;
			//_delay_ms(200);
			//TCCR3A=0X00;
			//PORTA = 0x00;
		//}
	}
	return 0;
}