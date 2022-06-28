/*
 * Mini_Project.c
 * Created: 2022.06.22
 * Author : 임이랑
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Lcd.h"
#include <stdio.h>
#include <stdlib.h>
#define open 0
#define error 3

unsigned int Door[4] = {523, 659, 783, 1046};
unsigned char R_PassWord[]="0000";					//최초 비밀번호 0000
int mode = 1;

SIGNAL(INT4_vect)
{
	cli();
	mode *= -1;
	sei();
}

SIGNAL(INT5_vect)
{
	cli();
	mode = 5;
	sei();
}

void music(int i)
{	//부저
	for(;i<5;i++)
	{
		ICR3 = 7372800 / Door[i]/5;
		TCCR3A = 0x40;
		_delay_ms(200);
		TCCR3A=0X00;
	}
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0) if(mode > 0) return 'R';
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

void On_board()
{
	int Error= 0;
	
	Lcd_Clear();		//LCD초기화
	Lcd_Pos(0, 0);		//LCD 위치설정
	Lcd_STR("PASSWORD?");
	
	while(1)
	{
		Error = On_board_Password();
		
		if(Error==1)										//비교 시 다를 경우
		{
			Lcd_Pos(1, 0);
			Lcd_STR("Error number");
			music(error);									//error 소리
			_delay_ms(1000);								//1s delay
			Lcd_password_clear();							//LCD 초기화
		}
		else if(Error == 2)											//비교 시 같은 경우
		{
			Lcd_Pos(1, 0);
			Lcd_STR("OPEN");
			music(open);									//Door Open 소리
			Motor();										//도어락 잠금장치 해제(모터)
			_delay_ms(1000);								//1s delay
			Lcd_password_clear();							//LCD 초기화
		}
		else if(Error == 3) 
		{
			return;
		}
	}
}

int On_board_Password()
{
	int i=0, Error=0;		//i = 배열위치, Error = 잘 못 입력했을 시 1
	unsigned char PassWord[5]="";
	
	for(;i<6;){
		if(mode == -1 || mode == 5)	return 3;										//모드 변경 시 main으로 돌아가기
			
		if(keyscan()!='\0' ){										//키패드에서 입력 받아오기
			PassWord[i] = keyscan();								//배열에 키패드에서 받아온 값 입력
			if(PassWord[i] >= 0x30 && PassWord[i]<=0x39)			//범위설정
			{	//0~9까지만 입력 가능
				Lcd_Pos(1, i);										//LCD 위치 설정
				Lcd_STR("*");										//숫자 대신 *을 출력하여 보안
			}
			else if(PassWord[i] == '#')
			{	//# : Clear
				Lcd_password_clear();								//LCD 초기화
				PassWord[0] = '\0';
				i=-1;
			}
			else if(PassWord[i] == '*')
			{	//* : 입력완료, 문자열 비교
				for(int j=0;j<4;j++)
				{
					if(R_PassWord[j] != PassWord[j]) Error = 1;		//저장된 비밀번호와 입력된 비밀번호 비교
				}
				
				if(Error==1)	return 1;									//비교 시 다를 경우
				else return 2;												//비교 시 같은 경우
			}//end of else if(PassWord[i] == '*')
			i++;
			_delay_ms(200);
			}//end of if(keyscan()!='\0')
		}//end of for(;i<6;)
}

void ON_terminal()
{
	char PassWord[5];
	int i=0, Error=0;
	
	Lcd_Clear();
	Lcd_Pos(0, 0);
	Lcd_STR("TERMINAL MODE");
	
	for(;i<6;)
	{
		PassWord[i]=getch();										//getch내부에 mode변경함수 있음.
		if(PassWord[i]=='R') return;								//mode변경 함수 return 'R' -> 모드 변경(On_Board)
		if(PassWord[i] >= 0x30 && PassWord[i] <= 0x39)				//숫자 외 다른 입력 제외
		{
			putch_USART0('*');										//숫자 대신 * 출력
			i++;
		}
		else if(PassWord[i] == '-')									
		{	//- : Clear
			putch_USART0('\r');
			putch_USART0('\n');
			i=0;
		}
		else if(PassWord[i] == '*')
		{	//* : 입력 완료, 문자 비교
			for(int j=0;j<4;j++) if(R_PassWord[j] != PassWord[j]) Error = 1;
			
			if(Error==1)
			{
				puts_USART0("Error Number!\r\n");
				music(error);
				_delay_ms(1000);
			}
			else
			{
				puts_USART0("OPEN!!\r\n");
				music(open);
				Motor();
				_delay_ms(1000);
			}
			PassWord[0] = '\0';
			i=0;
			Error = 0;
		}//end of else if(PassWord[i] == '*')
		//}//end of if(getch()!='\0')
	}//end of for(;i<6;)
}//end of void ON_terminal()

void Change_Password()
{
	Lcd_Clear();		//LCD초기화
	Lcd_Pos(0, 0);		//LCD 위치설정
	Lcd_STR("Identification");
	mode = 0;			//mode 초기화
	
	int Error;
	Error = On_board_Password();
	
	if(Error==1)										//비교 시 다를 경우
	{
		Lcd_Pos(1, 0);
		Lcd_STR("Error number");
		music(error);									//error 소리
		_delay_ms(1000);								//1s delay
		Lcd_password_clear();							//LCD 초기화
	}
	else if(Error == 2)									//비교 시 같은 경우
	{
		unsigned char New_PassWord[5]="";
		int i=0;
		Lcd_Clear();
		Lcd_Pos(0, 0);
		Lcd_STR("Change Password");						//LCD 첫번째 줄 출력
		_delay_ms(200);
		for(i=0;i<6;) 
		{
			char a=keyscan();							//키패드 입력
			if(a!='\0')									//keyscan()!='\0'으로 해놓았을 시 최초의 키 씹힘 현상 발생
			{
				New_PassWord[i] = a;
				if(New_PassWord[i] >= 0x30 && New_PassWord[i]<=0x39)
				{
					Lcd_Pos(1, i);
					Lcd_CHAR(New_PassWord[i]);
					if(i>4)								//password 최대 4글자 제한
					{									//화면 다시 변경모드로 초기화
						Lcd_Clear();
						Lcd_Pos(0, 0);
						Lcd_STR("MAX word : 4 !!");
						Lcd_Pos(1, 0);
						Lcd_STR("Re-Enter");
						_delay_ms(1000);
						Lcd_Clear();
						Lcd_Pos(0, 0);
						Lcd_STR("Change Password");
						i=-1;
					}
				}
				else if(New_PassWord[i] == '*')
				{	//입력완료
					for(int i=0;i<4;i++)
					{
						R_PassWord[i] = New_PassWord[i];
					}
					mode = 1;							//키패드 입력모드로 다시 초기화
					Error=0;							//Error 초기화
					_delay_ms(200);
					Lcd_Pos(1, 0);
					Lcd_STR("Change Complete!");
					_delay_ms(1000);
					return;
				}
				else if(New_PassWord[i]=='#')
				{	//입력 취소
					Lcd_Clear();
					Lcd_Pos(0, 0);
					Lcd_STR("Cancel Input");
					mode = 1;
					Error=0;
					_delay_ms(1000);
					return;
				}
				i++;
				_delay_ms(200);
			}
		}//end of for(;i<6;)
	}//end of else if(Error == 2)
	else if(Error == 3) 
	{
		music(2);
		mode = 1;
		return;
	}
	mode = 1;
	return;
}

int main(void)
{
    // A : KeyPad
	init_keypad();
	
	// 부저(PE3)
	DDRE = 0x08;
	TCCR3A = 0x00;
	TCCR3B = 0x19;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	// PE4 : 인터럽트4
	//DDRE = 0x00; 이미 부저에서 선언이 되어있음.
	EIMSK = (1<<INT4) | (1<<INT5);
	EICRB = (1<<ISC41) | (1<<ISC40) | (1<<ISC51) | (1<<ISC50);
	
	// UART
	init_USART0();
	
	// D : Motor
	DDRD = 0xff;
	
	// C, F : LCD
	DDRC = 0XFF;
	DDRG = 0xFF;
	
	Lcd_Init();
	unsigned char R_PassWord[]="0000";
	sei();
	
    while (1) 
    {
		if(mode==1) On_board();							//보드 키패드 입력 모드
		else if (mode == -1) ON_terminal();				//터미널 입력 모드
		else if (mode == 5)	Change_Password();			//비밀번호 변경 모드
    }//end of while
}//end of main

