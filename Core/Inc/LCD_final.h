/*
 * LCD_final.h
 *
 *  Created on: Oct 28, 2022
 *      Author: Admin
 */

#ifndef INC_LCD_FINAL_H_
#define INC_LCD_FINAL_H_

unsigned char pointer;

void show_result (long double out);

void LCD_Enable (void);
void LCD_SendCommand (unsigned char Command);
void LCD_Clear();
void LCD_Init();
void LCD_DisplayChar (unsigned char Data);
void LCD_DisplayString (char *s);

#endif /* INC_LCD_FINAL_H_ */
