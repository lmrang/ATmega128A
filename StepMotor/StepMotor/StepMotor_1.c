/*
 * StepMotor.c
 *
 * Created: 2022-06-23 오후 3:04:20
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/delay.h>


int main(void)
{
    DDRD = 0xff;
    while (1) 
    {
		PORTD = 0x10;
		_delay_ms(50);
		PORTD = 0x20;
		_delay_ms(50);
		PORTD = 0x40;
		_delay_ms(50);
		PORTD = 0x80;
		_delay_ms(50);
    }
}

