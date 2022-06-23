/*
 * PIEZO_BUTTON1.c
 *
 * Created: 2022-06-23 오전 10:11:22
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
volatile unsigned char soung_flag = 1;
	
SIGNAL(INT0_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[0] /5;
	TCCR3A = 0x40;
	soung_flag =1;
	sei();
}

SIGNAL(INT1_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[1]/5;
	TCCR3A = 0x40;
	soung_flag =1;
	sei();
}

SIGNAL(INT2_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[2]/5;
	TCCR3A = 0x40;
	soung_flag =1;
	sei();
}

SIGNAL(INT3_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[3]/5;
	TCCR3A = 0x40;
	soung_flag =1;
	sei();
}

SIGNAL(INT4_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[4]/5;
	TCCR3A = 0x40;
	soung_flag =1;
	sei();
}

SIGNAL(INT5_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[5]/5;
	TCCR3A = 0x40;
	soung_flag =1;
	sei();
}

SIGNAL(INT6_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[6]/5;
	TCCR3A = 0x40;
	soung_flag =1;
	sei();
}

SIGNAL(INT7_vect)
{
	cli();
	ICR3 = 7372800 / DoReMi[7]/5;
	TCCR3A = 0x40;
	soung_flag =1;
	sei();
}

int main()
{
	DDRE = 0x08;
	DDRD = 0X00;
	
	TCCR3A = 0x00;
	TCCR3B = 0x19;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	EICRA = 0XFF;
	EICRB = 0XFF;
	EIMSK = 0XFF;
	EIFR = 0XFF;
	sei();
	
	while(1)
	{
		if(soung_flag)
		{
			_delay_ms(1000);
			TCCR3A=0X00;
			soung_flag=0;
		}
	}
	
	return 0;
}