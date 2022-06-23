/*
 * CFile1.c
 *
 * Created: 2022-06-23 오전 9:31:29
 *  Author: PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

int main()
{
	unsigned char piano = 0;
	
	DDRB = 0X80;			//PB7 (OC1C)
	
	TCCR1A = (1<<COM1C0) | (1<<WGM11);  //0X0A;
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS10);	//0X19;
	TCCR1C = 0X00;
	TCNT1 = 0X0000;
	
	while(1)
	{
		ICR1 = 7372800 / DoReMi[piano];
		OCR1C = ICR1/2;		//50%듀티비
		piano++;
		if(8<piano) piano=0;
		_delay_ms(1000);
	}
	
	return 0;
}