/*
 * Motor.c
 *
 * Created: 2022-06-24 오전 11:52:49
 *  Author: PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

void Motor()
{
	for(int i=0;i<20;i++)
	{	//20스텝만 돌리기 (문열리는 동작)
		PORTD = 0x30;
		_delay_ms(20);
		PORTD = 0x90;
		_delay_ms(20);
		PORTD = 0xc0;
		_delay_ms(20);
		PORTD = 0x60;
		_delay_ms(20);
	}
}