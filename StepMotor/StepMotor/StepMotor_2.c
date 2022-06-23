/*
 * StepMotor_2.c
 *
 * Created: 2022-06-23 오후 3:09:52
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	DDRD = 0xff;
	while (1)
	{
		PORTD = 0x30;
		_delay_ms(30);
		PORTD = 0x90;
		_delay_ms(30);
		PORTD = 0xc0;
		_delay_ms(30);
		PORTD = 0x60;
		_delay_ms(30);
	}
}