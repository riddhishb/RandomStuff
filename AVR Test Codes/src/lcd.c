/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Created By: Riddhish Bhalodia

Refrences: Davide Gironi
	   Patrick Hood-Daniel

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

void Check_Busy()
{
	LCD_DDR = 0;
	LCD_CONTROL_PORT |= 1<<RW;
	LCD_CONTROL_PORT &= ~1<<RS;

	while (LCD_PORT >= 0x80){
		EN_Toggle();
	}
	LCD_DDR = 0xFF; 
}
void EN_Toggle()
{
	LCD_CONTROL_PORT |= 1<<EN;
	asm volatile ("nop");
	asm volatile ("nop");
	LCD_CONTROL_PORT &= ~1<<EN;
}

void Send_A_Command(unsigned char command)
{
	Check_Busy();
	LCD_PORT = command;
	LCD_CONTROL_PORT &= ~ ((1<<RW)|(1<<RS));
	EN_Toggle();
	LCD_PORT = 0;
}

void Send_A_Character(unsigned char character)
{
	Check_Busy();
	LCD_PORT = character;
	LCD_CONTROL_PORT &= ~ (1<<RW);
	LCD_CONTROL_PORT |= 1<<RS;
	EN_Toggle();
	LCD_PORT = 0;
}

void Send_A_String(char *StringOfCharacters)
{
	while(*StringOfCharacters > 0){
		Send_A_Character(*StringOfCharacters++);
	}
}

