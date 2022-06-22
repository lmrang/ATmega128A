/*
 * Timer16_4.c
 *
 * Created: 2022-06-22 오후 12:26:32
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char seg[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e};
unsigned int i=0;
volatile unsigned char FND_flag =0, edge_flag =0;

SIGNAL(TIMER3_CAPT_vect)
{	//PE7(ICP3)
	cli();
	//상승엣지에서 하강엣지까지의 시간은 계산
	unsigned int count;
	
	if(edge_flag == 0)
	{	//스위치가 눌리는 시간 측정
		//상승엣지
		//프리스케일러 1024, 하강엣지 캡처 트리거
		TCCR3B = (1<<CS32) | (1<<CS30);		//ICES3 = 0, 하강엣지에서 검출
		TCNT3 = 0;
		ICR3 = 0;
		edge_flag = 1;
	}
	
	else
	{	//스위치를 떼면
		//프리스케일러 1024, 상승엣지 캡쳐 트리거
		TCCR3B = (1<<ICES3) | (1<<CS32) | (1<<CS30);		//ICES3 = 1, 상승엣지에서 검출
		count = ICR3;
		
		i = count / 720;
		
		FND_flag = 1;
		edge_flag = 0;
	}
	sei();
}

int main()
{
	DDRA = 0XFF;
	DDRE = 0X00;
	
	TCCR3A = 0X00;
	TCCR3B = (1<<ICES3) | (1<<CS32) | (1<<CS30);
	
	ETIMSK = (1<<TICIE3);
	ETIFR |= 1<< ICF3;
	
	sei();
	
	PORTA = seg[0];
	while(1)
	{
		if(FND_flag)
		{
			if(i>15) i=15;
			
			PORTA = seg[i];
			FND_flag = 0;
		}
	}
	return 0;
}