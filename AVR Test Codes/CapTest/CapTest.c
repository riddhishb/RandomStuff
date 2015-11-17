// Code for measuring the capacitance of the sensor
// 1Mhz clock

/*//////////////////////////////////////////////////////////////////////////
Created by: Riddhish Bhalodia and Ankita Pasad

Electronic Design Lab Project : GRAIN HEALTH
//////////////////////////////////////////////////////////////////////////*/

#define VIN_PIN 	0
#define Vplus		1
#define Vminus		2

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "lcd.c"

int Num = 0;
int TimerInitVal = 65532;
int OutOfRange = 0;

ISR(TIMER1_OVF_vect){
	Num++;
	if(Num>1000){OutOfRange = 1;}
	TCNT1=TimerInitVal; // counter reset to zero;
}
void reset(){
	ASRC = 0x80 // Disable Analog Comparator
	TCCR1B=0x00; //stop timer
	TCCR1A = 0x00; //normal timer mode
	TIMSK=0x21; //Interrupt Mask Register for timer 1

	DDRB |= (1<<VIN_PIN)|(1<<Vminus);
	// Discahrge the Cap
	PORTB = PINB | (1<<Vminus);
	Num = 0;
	_delay_ms(2000);

}

void disp_cap(unsigned int n){
	Send_A_String("CapMeasure = ");
	_delay_ms(2);
	Send_An_Integer(n,4);
	_delay_ms(2);
	Send_A_String(" pF");
	_delay_ms(2);
}
int main(){
	// initilize the required pins
	////////////////////////////////////////////////////////////////////////
	LCD_CONTROL_DDR |= 1<<EN | 1<<RW | 1<<RS;

	_delay_ms(15);
	
	DDRC |= 1<<PINC0 | 1<<PINC1 ;

	Send_A_Command(0x01); //Clear Screen
	_delay_ms(2);
	Send_A_Command(0x38);
	_delay_us(50);
	Send_A_Command(0b00001110);
	_delay_us(50);	
	Send_A_String("Welcome!"); // 
	_delay_ms(1000);
	Send_A_Command(0x01);
	_delay_ms(2);

	// Configure Timer and Analog Comparator
	/////////////////////////////////////////////////////////////////////////
	reset();


	// The Main Loop
	/////////////////////////////////////////////////////////////////////////
	
	while(1){


	}


}
