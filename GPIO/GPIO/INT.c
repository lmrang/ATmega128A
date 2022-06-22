/*
 * INT.c
 *
 * Created: 2022-06-20 오전 9:55:44
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char count = 0;
SIGNAL(INT0_vect)
{
	count++;
	PORTA = count;
}

int main()
{
	DDRD = 0X00;
	DDRA = 0XFF;
	EIMSK =	1 << INT0;					//0X01;	//INT0 활성화
	EICRA = (1<< ISC01) | (1<<ISC00);	//EICRA = 0X03;			//0 b 0000 0011
	sei();								//전체 인터럽트 Enable
	
	while(1)
	{
		
	}
	return 0;
}