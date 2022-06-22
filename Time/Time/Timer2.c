/*
 * Time.c
 *
 * Created: 2022-06-21 오후 3:30:56
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x01;
unsigned char timer2cnt = 0;
unsigned char Shift_Flag = 0;
SIGNAL(TIMER0_OVF_vect);

int main(void)
{
	DDRC = 0XFF;
	TCCR2=0X05;
	TCNT2 = 180;
	
	TIMSK = 0X40;
	TIFR |= 1 << TOV2;
	sei();
	
	while(1)
	{
		PORTC = LED_Data;
	}
}

SIGNAL(TIMER2_OVF_vect)
{
	cli();
	TCNT2 = 180;
	timer2cnt++;
	if(timer2cnt == 50)
	{
		if(Shift_Flag == 0)
		{
			LED_Data <<= 1;
			if(LED_Data == 0x80) Shift_Flag = 1;
		}
		else
		{
			LED_Data >>= 1;
			if(LED_Data == 0x01) Shift_Flag = 0;
		}
		timer2cnt = 0;
	}
	sei();
}

