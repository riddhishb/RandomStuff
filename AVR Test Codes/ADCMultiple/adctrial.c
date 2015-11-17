#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "lcd.c"

int main(void)
{
LCD_CONTROL_DDR |= 1<<EN | 1<<RW | 1<<RS;
	_delay_ms(15);
	//DDRC |= 1<<PINC0 | 1<<PINC1 ;
	DDRC = 0xFF;
	Send_A_Command(0x01); //Clear Screen
	_delay_ms(2);
	Send_A_Command(0x38);
	_delay_us(50);
	Send_A_Command(0b00001110);
	_delay_us(50);	

ADCSRA |= 1<<ADPS2;
ADMUX |= (1<<REFS0) | (0<<REFS1);
ADCSRA |= 1<<ADIE;
ADCSRA |= 1<<ADEN;

sei();

ADCSRA |= 1<<ADSC;

while (1)
{
}
}
ISR(ADC_vect)
{
uint8_t theLowADC = ADCL;
uint16_t theTenBitResults = ADCH<<8 | theLowADC;
Send_A_Command(0x01);
	_delay_ms(2);        
Send_An_Integer(theTenBitResults, 4);
_delay_ms(50);
ADCSRA |= 1<<ADSC; 
}
