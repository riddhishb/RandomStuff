#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <util/delay.h>
#include "lcd.c"
#include "math.h"

//A0 - Vsp
//A1 - Vrp
//A2 - Vzp
uint16_t compare = 0;
int count = 0;
int count1 = 0;
uint16_t vsp = 0;
uint16_t vrp = 0;
uint16_t vzp = 0;
uint16_t vsp_mod = 0;
uint16_t vrp_mod = 0;
uint16_t vzp_mod = 0;
uint16_t final = 0;
float x1 = 0;
float x2 = 0;
float x3 = 0;
float x4 = 0;
int res = 0;
int res_prev = 0;
int res_prev_prev = 0;
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
ADMUX  = 0x40;
ADCSRA |= 1<<ADIE;
ADCSRA |= 1<<ADEN;

sei();

ADCSRA |= 1<<ADSC;
count = 0;
while (1)
{	

}
}

ISR(ADC_vect)
{
   // PORTC = 0b00001000;
uint8_t theLow  ;
uint16_t theTenBitResult;
   theLow = ADCL;
   theTenBitResult =ADCH<<8 | theLow;
switch (ADMUX)
{
case 0x40:

      if(count<80){
        final = final + theTenBitResult;
        count++;
     }
      else{
        final = final/80;
        vsp = theTenBitResult;
        Send_A_Command(0x01);
	_delay_ms(2);
	Send_A_Command(0x80);
	_delay_ms(2);
        Send_A_String("0");        
	Send_An_Integer(vsp, 4);
	_delay_ms(250);
        count = 0;
	final = 0;
	vsp_mod = vsp*vsp;
  }

//ADMUX = 0x42;
//Send_A_Command (0xC0);
//Send_An_Integer(ADMUX,4);
//Send_A_String("OUT");
break;

case 0x41:

	if(count<80){
        	final = final + theTenBitResult;
        	count++;
      	}
      	else{
         	final = final/80;
        	vrp = final;
		Send_A_Command(0x85);
		_delay_ms(2);
		Send_A_String("1");
        	Send_An_Integer(vrp,4);
        	_delay_ms(50);
        	count = 0;
		final = 0;
		vrp_mod = vrp*vrp;
  	}

ADMUX = 0x40;
break;

case 0x42:
if(count<80){
        	final = final + theTenBitResult;
        	count++;
      	}
      	else{
         	final = final/80;
        	vzp = final;
		Send_A_Command(0x8A);
		_delay_ms(2);
		Send_A_String("2");
        	Send_An_Integer(vzp,4);
        	_delay_ms(50);
        	count = 0;
		final = 0;
		vzp_mod = vzp*vzp;
		//Send_A_Command(0x01);

  	}
ADMUX = 0x41;
break;

/*case 0x00:
		if(count1<800) count1++;
else{
		x1 = vsp_mod - vrp_mod - vzp_mod;
		x2 = 2*vzp*vrp;		
		x3 = x1/x2;
		if(x3<1) {
		x4 = acos(x3);
		Send_A_Command(0xC0);
		Send_An_Integer(x4, 4);
}
		else {
		Send_A_Command(0xC0);
		Send_A_String("Invalid Readings");
}
//ADMUX = 0x40;
}

break;*/
default:
//Default code
break;
}

//Send_A_Command(0xC0);
  //  _delay_ms(2);
    //Send_An_Integer(compare,4);
    //_delay_ms(200);
    // Simple Processing of the compare value
    

 ADCSRA |= 1<<ADSC;
}
