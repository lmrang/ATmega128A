/*
 * PWM_2.c
 *
 * Created: 2022-06-22 오후 4:36:19
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int Light = 0;
volatile unsigned char Light_flag = 1;

SIGNAL(INT4_vect)
{	//LED 끄기
	cli();
	Light = 0;
	Light_flag = 1;
	sei();
}

SIGNAL(INT5_vect)
{	//LED 점차 어둡게
	cli();
	Light -= 51;
	if(Light < 0) Light=0;
	Light_flag =1;
	sei();
}

SIGNAL(INT6_vect)
{	//LED 점차 밝게
	cli();
	Light += 51;
	if(Light > 255) Light=255;
	Light_flag =1;
	sei();
}

SIGNAL(INT7_vect)
{	//LED 밝기 100%
	cli();
	Light = 255;
	Light_flag =1;
	sei();
}

int main() 
{
	DDRB = 0xff;
	DDRE = 0X00;
	
	TCCR2 = (1<<WGM20) | (1<<COM21) | (0<<CS22) | (1<<CS21) | (0<<CS20);		//PWM / 분주비 8
	TCNT2 = 0;
	
	EICRB = 0XFF;
	EIMSK = 0XF0;
	EIFR = 0XF0;
	
	sei();
	
	while(1)
	{
		if(Light_flag)
		{
			OCR2 = Light;		//PB7
			Light_flag = 0;
		}
	}
}