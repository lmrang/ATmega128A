#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

char KeyScan(void)
{
	char KeyBuf=0xFF;  // 키 값이 들어갈 버퍼, 초기값 0xFF
	DDRC = 0; PORTC = 0xFF;  // 포트 초기값, 입력핀 내부풀업저항 사용
	DDRC=0x10; PORTC&=~0x10; _delay_us(5); // 1번째 세로줄 선택
	if(!(PINC&1))KeyBuf='1';
	if(!(PINC&2))KeyBuf='4';
	if(!(PINC&4))KeyBuf='7';
	if(!(PINC&8))KeyBuf='*'; //*
	DDRC=0; PORTC=0xFF; // 1번째 세로줄 해제(대기)
	
	DDRC=0x20; PORTC&=~0x20; _delay_us(5); // 2번째 세로줄 선택
	if(!(PINC&1))KeyBuf='2';
	if(!(PINC&2))KeyBuf='5';
	if(!(PINC&4))KeyBuf='8';
	if(!(PINC&8))KeyBuf='0';
	DDRC=0; PORTC=0xFF; // 2번째 세로줄 해제(대기)
	
	DDRC=0x40; PORTC&=~0x40; _delay_us(5); // 3번째 세로줄 선택
	if(!(PINC&1))KeyBuf='3';
	if(!(PINC&2))KeyBuf='6';
	if(!(PINC&4))KeyBuf='9';
	if(!(PINC&8))KeyBuf='#'; //#
	DDRC=0; PORTC=0xFF; // 3번째 세로줄 해제(대기)
	
	return KeyBuf; // Key 없으면 0xFF 리턴
}

int main()
{
	DDRC = 0x0f;
	DDRE = 0xff;
	char key;
	
	while(1)
	{
		key=KeyScan();
		if(key == '1') PORTE = 0x01;
	}
	
	return 0;
}