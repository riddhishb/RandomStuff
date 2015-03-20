#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <util/delay.h>
#include "lcd.c"

uint16_t compare = 0;
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
ADMUX |= (1<<REFS0)|(0<<REFS1) ;
//ADMUX |= (1<<REFS1);
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
   // PORTC = 0b00001000;
uint8_t theLow = ADCL;
uint16_t theTenBitResult = ADCH<<8 | theLow;

//switch (ADMUX)
//{
//case 0x40:
Send_A_Command(0x01);
        _delay_ms(2);
        Send_An_Integer(theTenBitResult,4);
	compare = ADCH<<8 | theLow;;
       Send_A_String(",");
//	_delay_ms(30);
/*
ADMUX = 0x41;
break;
case 0x41:

        _delay_ms(2);
        
        //Send_An_Integer(theTenBitResult,4);
        //Send_A_String(",");
//	_delay_ms(300);
ADMUX = 0x42;
break;

case 0x42:
//Send_A_Command(0xC0);
       _delay_ms(2);
        
        //Send_An_Integer(theTenBitResult,4);
       // Send_A_String(",");

//	_delay_ms(300);
ADMUX = 0x43;
break;

case 0x43:

        _delay_ms(2);
        
       // Send_An_Integer(theTenBitResult,4);
       // Send_A_String(",");

	//_delay_ms(300);
ADMUX = 0x40;
break;
default:
//Default code
break;
}*/

Send_A_Command(0xC0);
    _delay_ms(2);
    Send_An_Integer(compare,4);
    _delay_ms(200);
    // Simple Processing of the compare value
    

    if(compare < 102){
        PORTC = 0b00000000;
    }
    else if((compare>102)&&(compare<204)){
                
                PORTC =0b00000001;
    }
    else if((compare>204)&&(compare<306)){ 
     PORTC =0b00000010;
        }
    else if((compare>306)&&(compare<408)){ 
               PORTC =0b00000011;
        }
    else if((compare>408)&&(compare<510)){ 
                PORTC =0b01000000;
        }
    else if((compare>510)&&(compare<612)){ 
               PORTC =0b01000001;
        }
    else if((compare>612)&&(compare<714)){ 
               PORTC =0b01000010;
        }
    else if((compare>714)&&(compare<816)){ 
              PORTC =0b01000011;
        }
    else if((compare>816)&&(compare<918)){ 
              PORTC =0b10000000;
        }
    else if((compare>918)&&(compare<1025)){ 
              PORTC =0b10000001;
        }
 ADCSRA |= 1<<ADSC;
}
