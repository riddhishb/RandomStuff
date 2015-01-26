/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Created By: Riddhish Bhalodia

Refrences: Davide Gironi
	   Patrick Hood-Daniel

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "dht.h"
#include "dht.c"

#include "lcd.h"
#include "lcd.c"

int main(void){

	char printbuff[100];
	
	LCD_CONTROL_DDR |= 1<<EN | 1<<RW | 1<<RS;
	_delay_ms(15);
	
	DDRC |= 1<<PINC0 | 1<<PINC1 ;

	Send_A_Command(0x01); //Clear Screen
	_delay_ms(2);
	Send_A_Command(0x38);
	_delay_us(50);
	Send_A_Command(0b00001110);
	_delay_us(50);	
	
	int8_t temperature = 0;
	int8_t humidity = 0;
	
	while(1){
		if(dht_gettemperaturehumidity(&temperature, &humidity) != -1) {
			
			
			Send_A_Command(0x01); //Clear Screen
			_delay_ms(2);
			
			// White LED Toggles at every reading
			PORTC ^= 1<<PINC0;
			PORTC &= ~(1<<PINC1);

			// Display Temperature			
			itoa(temperature, printbuff, 10);
			Send_A_String("Temp = ");
			Send_A_String(printbuff);
			Send_A_String(" 'C");
			
			// Display Humidity
			itoa(humidity, printbuff, 10);
			Send_A_Command(0xC0);
			Send_A_String("RH = ");
			Send_A_String(printbuff);
			Send_A_String(" %");

		} else {
			// RED LED Lights if the sensor is not functioning properly.
			PORTC = PINC | 1<<PINC1;			
		}

		_delay_ms(1500);
	}
	
	return 0;
}


