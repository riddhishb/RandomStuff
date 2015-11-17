// Code for measuring the capacitance of the sensor
// 1Mhz clock

/*//////////////////////////////////////////////////////////////////////////
Created by: Riddhish Bhalodia and Ankita Pasad

Electronic Design Lab Project : GRAIN HEALTH
//////////////////////////////////////////////////////////////////////////*/

#define discharge_pin 	0
#define Vplus			1
#define Vminus			2

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "lcd.c"

int level = 0;
int counter = 0;
int Num = 0;
int ovf = 0;


int main(){

	//TCCR1B=0x00; //stop timer

	LCD_CONTROL_DDR |= 1<<EN | 1<<RW | 1<<RS;

	_delay_ms(15);

	Send_A_Command(0x01); //Clear Screen
	_delay_ms(2);
	Send_A_Command(0x38);
	_delay_us(50);
	Send_A_Command(0b00001110);
	_delay_us(50);	
	Send_A_String("Welcome!"); // 
	//_delay_ms(5000);
//	Send_A_Command(0x01);
//	_delay_ms(2); 

	/*TCCR1A = 0x00; //normal timer mode
	TIMSK=0x21; //Interrupt Mask Register for timer 1  

	//pinMode(discharge_pin, OUTPUT);
	DDRB |= (1<<discharge_pin);
	ACSR = 0x80; // Disable Analog Comparator
	
	sei();
	DDRB |= (1<<discharge_pin)|(1<<Vminus);
	// Discahrge the Cap
	PORTB = PINB | (1<<Vminus);
	Num = 0;
	_delay_ms(2000);
*/
	while(1){
/*		counter = 0;
		LCD_CONTROL_DDR |= 1<<EN | 1<<RW | 1<<RS;

		_delay_ms(15);
		
		DDRC |= 1<<PINC0 | 1<<PINC1 ;
		
		ACSR=0x80; //analog comparator is turned off

		ACSR=0x47; // Analog Comparator Control and Status Register
		//DIDR1=0x03; //Digital Input Disable Register

		TCNT1=0x00; // counter reset to zero;
		PORTB = PINB | (1<<discharge_pin);  // apply hig voltage to start charging
		TCCR1B = 0xC0; //start timer (clock prescaler /1)
		while (level&&!ovf) {}
		*/
	}
	return 0;
}
/*
ISR(TIMER1_CAPT_vect) {

	TCCR1B=0x00; //stop timer
	counter=ICR1; //saving counter value to variable      
	level=0; // capacitor's voltage reached required level
	ACSR=0x80; //analog comparator is turned off

	if (counter>3) { // to avoid false result with no capacitor 
	if (!ovf) {Send_A_Command(0x01); _delay_ms(2);}
	// because with 200nF capacitor counter stopped by 82. 
//	  cap=(double)counter/82.0*200.0;

	 // showing result in nF or µF automatically   
//	if (cap<1000) {lcd.print(cap); lcd.print(" nanoF");}
//	  else {lcd.print(cap/1000.0); lcd.print(" microF");}
	}
	Send_An_Integer(counter,6);
	ovf=0;

}

ISR(TIMER1_OVF_vect) {
	ovf=1;
	Send_A_Command(0x01);
	_delay_ms(2);
	//Send_A_String('Overflow');
	//_delay_ms(2);
}

*/