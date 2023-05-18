/*
 * keypad.h
 *
 *  Created on: Oct 29, 2022
 *      Author: Admin
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

char KP45[20];

unsigned char check_but();
void scan_row(unsigned char r);
unsigned char check_col();
unsigned char get_key ();
char key2char(unsigned char key);
#endif /* INC_KEYPAD_H_ */
