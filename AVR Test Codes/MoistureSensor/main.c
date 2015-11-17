#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <util/delay.h>
#include "lcd.c"

long int count = 0;
long int result = 0;
int avgcnt=0;
int temp1 =0;
int answer = 0;

int main(void)
{
	LCD_CONTROL_DDR |= 1<<EN | 1<<RW | 1<<RS;
	_delay_ms(15);
	DDRC |= 1<<PINC0 | 1<<PINC1 ;
	
	Send_A_Command(0x01); //Clear Screen
	_delay_ms(2);
	Send_A_Command(0x38);
	_delay_us(50);
	Send_A_Command(0b00001110);
	_delay_us(50);	
	

	ADCSRA |= 1<<ADPS2;
	ADMUX |= (1<<REFS0) | (1<<REFS1);
	ADCSRA |= 1<<ADIE;
	ADCSRA |= 1<<ADEN;
	sei();

	ADCSRA |= 1<<ADSC;

	while (1)
	{	
	}
	return 0;
}


ISR(ADC_vect)
{
	uint8_t theLowADC = ADCL;
	uint16_t res = ADCH<<8 | theLowADC;
	result = result + res;
	Send_A_Command(0x01);
        _delay_ms(2);
        Send_A_String("Result = ");
        Send_An_Integer(res,4);
	_delay_ms(100);
	/* count = count +1;
	if(count == 1000){
		PORTC ^= 1<<PINC0;
		result = result/1000;	
		answer = answer +result;
		avgcnt = avgcnt + 1;
		if(avgcnt == 2){
			answer = answer/2;
			Send_A_Command(0x01);
			_delay_ms(2);
			Send_A_String("Result = ");
			Send_An_Integer(answer,4);
			avgcnt = 0;
			answer = 0;
		}		
		result = 0;
		count = 0;		
	}*/
	
	_delay_ms(1);
	ADCSRA |= 1<<ADSC;
} 
