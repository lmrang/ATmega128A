/*
 * StepMotor4.c
 *
 * Created: 2022-06-23 오후 3:20:05
 *  Author: PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DIR_L 0
#define DIR_R 1

unsigned char timer0Cnt = 0, mot_cnt = 0;
volatile unsigned char dir = DIR_R;

unsigned char Step[] = {0x90, 0x80, 0xc0, 0x40, 0x60, 0x20, 0x30, 0x10};

SIGNAL(TIMER0_OVF_vect)
{	//모터 방향 전환
	cli();
	
	TCNT0 = 180;
	timer0Cnt++;
	if(timer0Cnt == 200)
	{
		dir^=1;			//dir을 DIR_L(0)과 DIR_R(1) 바꿔줌
		timer0Cnt = 0;	//약 2s
	}
	sei();
}

SIGNAL(TIMER1_OVF_vect)
{	//모터 회전
	cli();
	
	//TCNT1H = 0xfb;
	//TCNT1L = 0x0d;
	TCNT1 = 65400;
	
	PORTD = Step[mot_cnt];
	if(dir == DIR_R)
	{
		if(mot_cnt++ == 7) mot_cnt = 0;
	}
	else if(mot_cnt-- == 0) mot_cnt = 7;
	
	sei();
}

int main()
{
	DDRB = 0x20;
	PORTB &= ~0x20;
	DDRD = 0xf0;
	
	//8비트 타이머
	TCCR0 = (1<<CS02) | (1<<CS12) | (1<<CS22);		//1024분주
	TCNT0 = 180;									// 7372800 / 1024 = 7200
	
	//16비트 타이머
	TCCR1A = 0;			
	TCCR1B = (1 << CS12);
	TCNT1 = 65400;
	//TCNT1H = 0xFB;
	//TCNT1L = 0x0D;
	TIMSK = (1<<TOIE0) | (1 << TOIE1);
	TIFR = 0x05;
	
	sei();
	
	while(1) {}
	
	return 0;
}