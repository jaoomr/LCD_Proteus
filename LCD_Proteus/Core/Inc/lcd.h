/*
 * lcd.h
 *
 *  Created on: Nov 3, 2020
 *      Author: joaop
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include<stdint.h>
#include "main.h"

void LCD_Init();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char ,char ,const char*);
void LCD_Custom_Char (unsigned char loc, unsigned char *msg);
void LCD_Clear();

#endif /* INC_LCD_H_ */
