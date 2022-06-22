/*
 * LCDTest.c
 *
 * Created: 2022-06-20 오후 2:53:29
 * Author : PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int x=0;
	Byte str1[15];
	DDRA = 0XFF;
	DDRG = 0xff;
	Lcd_Init();

    while (1) 
    {
		for(int i=2;i<=9;i++){
			Lcd_Clear();
			Lcd_Pos(0,0);
			Lcd_STR("****GUGUDAN****");
			for(int j=1;j<=9;j++){
				Lcd_Pos(1,2);
				sprintf(str1, "%d x %d = %d", i, j, i*j);
				Lcd_STR(str1);
				_delay_ms(1000);
			}
		}
    }
	return 0;
}

