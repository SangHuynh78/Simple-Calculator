/*
 * LCD_finall.c
 *
 *  Created on: Oct 28, 2022
 *      Author: Admin
 */
#include "main.h"
#include "LCD_final.h"

#define LCD_EN	GPIO_PIN_10
#define LCD_RS	GPIO_PIN_11

void show_result (long double out)
{
	int ans, counter=10, j=0;
	char ANS[10]={0}, TERM [3]={0};

	if (out == '@' || out>= 10000000000 || out<= -10000000000)
		{
			LCD_Clear();
			LCD_DisplayString("MATH ERROR");
		}
	else
	{
		if (out<0) {out = -out; ANS[0] = '-';}
		//tách kí tự phần nguyên
		ans= (int)out/1;
		ANS[1] = ans/(10000000000) +48;
		ans = ans % (10000000000);
		ANS[2] = ans/(1000000000) +48;
		ans = ans % (1000000000);
		ANS[3] = (ans/(100000000) +48);
		ans = ans % (100000000);
		ANS[4] = (ans/(10000000) +48);
		ans = ans % (10000000);
		ANS[5] = (ans/(1000000) +48);
		ans = ans % (1000000);
		ANS[6] = (ans/(100000) +48);
		ans = ans % (100000);
		ANS[7] = (ans/(10000) +48);
		ans = ans % (10000);
		ANS[8] = (ans/1000 +48);
		ans = ans % 1000;
		ANS[9] = (ans/100 +48);
		ans = ans % 100;
		ANS[10] = (ans/10 +48);
		ANS[11] = (ans%10 +48);
		for (int i = 1; i<=11; i++)
		{
			if (ANS[i] != '0') {counter = i; i = 100;}
			else counter = 11;
		}
		if(ANS[0]=='-') ANS[--counter] = '-';
		//tách ký tự phần thập phân
		ans = 100000*(out - (int)out/1)+ 1;	//bù sai số
		ans /=10;
		TERM[0] = ans/1000 +48;
		ans = (int)ans%1000;
		TERM[1] = ans/100 +48;
		ans = (int)ans%100;
		TERM[2] = ans/10 +48;
		TERM[3] = (int)ans%10 +48;
		for (int i= 0; i<= 3; i++)	//xác định số chữ số sau dấu thập phân
		{
			if (TERM[i] != '0') j = i+2;
		}

		for (int i = counter; i<=11; i++ ) //xuất phần nguyên
		{
			LCD_SendCommand(0xC0 +i +(4-j));
			LCD_DisplayChar(ANS[i]);
		}
		//xuất phần thập phân nếu có
		if (TERM[0] != '0' || TERM[1] != '0' || TERM[2] != '0' || TERM[3] != '0')
		{
			LCD_DisplayChar('.');
			for (int i = 0;i <j; i++)
			{
				LCD_DisplayChar(TERM[i]);
			}
		}
		LCD_SendCommand(0x02);
	}
}

void LCD_Enable (void)
{
	HAL_GPIO_WritePin(GPIOB, LCD_EN, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, LCD_EN, 0);
	HAL_Delay(1);
}

void LCD_SendCommand (unsigned char Command)
{
	HAL_GPIO_WritePin(GPIOB, LCD_RS, 0);
	GPIOA-> ODR = Command;
	LCD_Enable();
}

void LCD_Clear()
{
	LCD_SendCommand(0x01);
	HAL_Delay(1);
	pointer = 0;
}

void LCD_Init()
{
	LCD_SendCommand(0x38);
	HAL_Delay(1);
	LCD_SendCommand(0x0C);
	HAL_Delay(1);
	LCD_SendCommand(0x06);
	HAL_Delay(1);
	LCD_Clear();
}

void LCD_DisplayChar (unsigned char Data)
{
	HAL_GPIO_WritePin(GPIOB, LCD_RS, 1);
	GPIOA-> ODR = Data;
	LCD_Enable();
	pointer ++;
	if (pointer >=16) {LCD_SendCommand(0x18);}
}

void LCD_DisplayString (char *s)
{
	pointer = 0;
	while (*s)
	{
		LCD_DisplayChar (*s);
		s++;
	}
}
