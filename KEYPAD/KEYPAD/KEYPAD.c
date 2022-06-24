/*
 * KEYPAD.c
 *
 * Created: 2022-06-23 오후 4:02:07
 * Author : PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char keyScan();

int main(void)
{
	DDRA = 0xF8;		//0b 1111 1000	출력(R), 입력(C)
	DDRE = 0xff;
	unsigned char key;
	
    while (1) 
    {
		key = keyScan();
		if(key == '1') PORTE = 0x01;
    }
	return 0;
}

unsigned char keyScan()
{
	PORTA = 0xF7;		//0b 1111 0111
	if(PINA == 0xF6)	    return '1';
	else if(PINA == 0xFD)	return '2';
	else if(PINA == 0xFB)	return '3';
	_delay_ms(10);
	
	PORTA = 0xEF;		//0b 1110 1111
	if(PINA == 0xFE)		return '4';
	else if(PINA == 0xFD)	return '5';
	else if(PINA == 0xFB)	return '6';
	_delay_ms(10);
	
	PORTA = 0xDF;		//0b 1101 1111
	if(PINA == 0xFE)		return '7';
	else if(PINA == 0xFD)	return '8';
	else if(PINA == 0xFB)	return '9';
	_delay_ms(10);
	
	PORTA = 0xBF;		//0b 1011 1111		즉, 0(low)이 signal
	if(PINA == 0xFE)		return '*';
	else if(PINA == 0xFD)	return '0';
	else if(PINA == 0xFB)	return '#';
	_delay_ms(10);
}
