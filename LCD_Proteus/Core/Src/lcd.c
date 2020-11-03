/*
 * lcd.c
 *
 *  Created on: Nov 3, 2020
 *      Author: joaop
 */
#include "main.h"
#include "lcd.h"


void writePort(char x){ // Função auxiliar para escrever na porta 8 bits
	int value;
	value = x & 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, value);
	value = x & 0x02;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, value);
	value = x & 0x04;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, value);
	value = x & 0x08;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, value);
	value = x & 0x10;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, value);
	value = x & 0x20;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, value);
	value = x & 0x40;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, value);
	value = x & 0x80;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, value);
}


void LCD_Init()  // Inicializa
{
	HAL_Delay(15);
    LCD_Command(0x38);
    LCD_Command(0x01);
    LCD_Command(0x0c);
    LCD_Command(0x06);
}

void LCD_Clear() // Limpa o display
{
    	LCD_Command(0x01);
}

void LCD_Command(char cmd) // Envia comandos para o display
{

	writePort(cmd);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
	asm("nop");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	HAL_Delay(3);
}

void LCD_Char(char dat) // Escreve um caractere no display
{
	writePort(dat);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
	asm("nop");
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	HAL_Delay(1);
}

void LCD_String(const char *msg) // Escreve uma string no display
{
	while((*msg)!=0)
	{
	  LCD_Char(*msg);
	  msg++;
	}
}


void LCD_Custom_Char (unsigned char loc, unsigned char *msg) // Grava caracteres especiais na cgram
{
    unsigned char i;
    if(loc<8)
    {
     LCD_Command (0x40 + (loc*8));
     for(i=0;i<8;i++)
        LCD_Char(msg[i]);
    }
}

void LCD_String_xy(char row,char pos,const char *msg) // Escreve string na posição X Y desejada
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f);
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);
        LCD_Command(location);
    }
    LCD_String(msg);
}
