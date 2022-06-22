/*
 * FND3.c
 *
 * Created: 2022-06-17 오후 4:34:33
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
unsigned char seg[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e};
	
int main()
{
	DDRA = 0xff;
	DDRF = 0x0f;
	int count = 0;
	int t=0, h=0, ten=0, one=0;
	while(1)
	{
		t = count/1000;				//천의 자리
		h = count / 100 % 10;		//백의 자리
		ten = count/10 % 10;		//십의 자리
		one = count % 10;			//일의 자리
		for(int i=0;i<12;i++)		//잔상... 없으면 잔상이 눈에 보임;
		{
			PORTF = 0xfe;			//11110111 : 천의 자리 (0이 켜진자리)
			PORTA = seg[t];
			_delay_ms(2);
			
			PORTF = 0xfd;			//11111011 : 백의 자리
			PORTA = seg[h];
			_delay_ms(2);
			
			PORTF = 0xfb;			//11111101 : 십의 자리
			PORTA = seg[ten];
			_delay_ms(2);
			
			PORTF = 0xf7;			//11111110 : 일의 자리
			PORTA = seg[one];
			_delay_ms(2);
		}
		count++;					//카운트 ++
	}
	return 0;
}
