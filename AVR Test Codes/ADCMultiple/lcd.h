/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Created By: Riddhish Bhalodia

Refrences: Davide Gironi
	   Patrick Hood-Daniel

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LCD_H_
#define LCD_H_

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#define LCD_PORT 			PORTD
#define LCD_DDR     			DDRD
#define LCD_CONTROL_PORT 		PORTB
#define LCD_CONTROL_DDR 	        DDRB
#define EN	 			4
#define RW 		   		3
#define RS 			        2

void Check_Busy(void);
void EN_Toggle(void);
void Send_A_Command(unsigned char command);
void Send_A_Character(unsigned char character);
void Send_A_String(char *StringOfCharacters);

#endif
