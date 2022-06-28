/*
 * keypad.c
 *
 * Created: 2022-06-24 오전 11:51:02
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

void init_keypad()
{
	DDRA = 0xF8; //0b 1111 1000		출력(R), 입력(C)
	PORTA = 0x07; //0b 0000 0111	1이 signal
}

unsigned char keyscan()
{
	PORTA = 0x08; //0b 0000 1000	R0줄 ON
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '1';		//0b 0000 0001
	else if((PINA & 0x07) == 0x02) return '2';	//0b 0000 0010
	else if((PINA & 0x07) == 0x04) return '3';	//0b 0000 0100
	_delay_ms(10);
	
	PORTA = 0x10;		// 0x10 R1 ON
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '4';		//0b 0000 0001
	else if((PINA & 0x07) == 0x02) return '5';	//0b 0000 0010
	else if((PINA & 0x07) == 0x04) return '6';	//0b 0000 0100
	_delay_ms(10);
	
	PORTA = 0x20;		// 0x20 R2 ON
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '7';		//0b 0000 0001
	else if((PINA & 0x07) == 0x02) return '8';	//0b 0000 0010
	else if((PINA & 0x07) == 0x04) return '9';	//0b 0000 0100
	_delay_ms(10);
	
	PORTA = 0x40;		// 0x40 R3 ON
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '*';		//0b 0000 0001
	else if((PINA & 0x07) == 0x02) return '0';	//0b 0000 0010
	else if((PINA & 0x07) == 0x04) return '#';	//0b 0000 0100
	_delay_ms(10);
	
	//return 0;
}