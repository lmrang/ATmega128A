/*
 * PWM.c
 *
 * Created: 2022-06-22 오후 4:24:22
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void)
{
	unsigned char Light = 0;
	
	DDRB = 0xff;
	
	TCCR0 = (1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<CS02) | (1<<CS01) | (0<<CS00);		//PWM / 분주비 256
	TCNT0 = 0X00;
    while (1) 
    {
		for(Light = 0;Light < 255;Light++)
		{
			OCR0 = Light;		//PB4
			_delay_ms(10);
		}
		for(Light=255;Light>0;Light--)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
    }
}

