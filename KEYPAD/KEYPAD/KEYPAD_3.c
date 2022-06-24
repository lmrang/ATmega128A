/*
 * keyT.c
 *
 * Created: 2022-06-23 오후 5:23:44
 *  Author: Cking
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

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
	
	return 0;
}
int main()
{
	DDRC = 0xFf;
	init_keypad();
	
	while(1){
		unsigned char key = keyscan();
		if(key == '1') PORTC = 0x01;
		else if(key == '2') PORTC = 0x02;
		else if(key == '3') PORTC = 0x03;
		else if(key == '4') PORTC = 0x04;
		else if(key == '5') PORTC = 0x05;
		else if(key == '6') PORTC = 0x06;
		else if(key == '7') PORTC = 0x07;
		else if(key == '8') PORTC = 0x08;
		else if(key == '9') PORTC = 0x09;
		else if(key == '0') PORTC = 0x00;
	}
	return 0;
}