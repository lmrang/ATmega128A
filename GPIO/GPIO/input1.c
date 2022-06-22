/*
 * input1.c
 *
 * Created: 2022-06-17 오후 3:19:59
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>



int main()
{
	DDRD = 0x00;	//입력
	DDRA = 0xFF;	//출력
	while(1)
	{
		if(PIND == 0x01)
		{
			_delay_ms(200);
			PORTA = 0x01;
			_delay_ms(1000);
			PORTA = 0x00;
		}
	}
	return 0;
}