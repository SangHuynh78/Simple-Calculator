/*
 * keypad4x5.c
 *
 *  Created on: Oct 29, 2022
 *      Author: Admin
 */
#include "main.h"
#include "keypad.h"

char KP45[] = {"CDP+789-456x123/0.A="};
#define row1	GPIO_PIN_4
#define row2	GPIO_PIN_6
#define row3	GPIO_PIN_7
#define row4	GPIO_PIN_8
#define row5	GPIO_PIN_9
#define col1	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)
#define col2	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)
#define col3	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)
#define col4	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)

unsigned char check_but()
{
	HAL_GPIO_WritePin(GPIOB, row1 , 0);
	HAL_GPIO_WritePin(GPIOB, row2 , 0);
	HAL_GPIO_WritePin(GPIOB, row3 , 0);
	HAL_GPIO_WritePin(GPIOB, row4 , 0);
	HAL_GPIO_WritePin(GPIOB, row5 , 0);
	if (!col1 || !col2 || !col3 || !col4) return 1; //co nut dc nhan
	return 0;
}

void scan_row(unsigned char r)
{
	HAL_GPIO_WritePin(GPIOB, row1 , 1);
	HAL_GPIO_WritePin(GPIOB, row2 , 1);
	HAL_GPIO_WritePin(GPIOB, row3 , 1);
	HAL_GPIO_WritePin(GPIOB, row4 , 1);
	HAL_GPIO_WritePin(GPIOB, row5 , 1);
	if (r == 1) HAL_GPIO_WritePin(GPIOB, row1 , 0);
	if (r == 2) HAL_GPIO_WritePin(GPIOB, row2 , 0);
	if (r == 3) HAL_GPIO_WritePin(GPIOB, row3 , 0);
	if (r == 4) HAL_GPIO_WritePin(GPIOB, row4 , 0);
	if (r == 5) HAL_GPIO_WritePin(GPIOB, row5 , 0);
}
unsigned char check_col()
{
	if (!col1) return 1;
	if (!col2) return 2;
	if (!col3) return 3;
	if (!col4) return 4;
	return 0;
}
unsigned char get_key ()
{
	unsigned char row, col=0;
	if (check_but())
	{
		HAL_Delay(50);
		if (check_but())
		{
			for (row = 1; row <= 5; row ++)
			{
				scan_row(row);
				col = check_col();
				if (col) return (((row-1)*4) +col);
			}
		}
	}
	return 0;
}
char key2char(unsigned char key)
{
	if (key && key<=20) return KP45[key-1];
	return 0;
}
