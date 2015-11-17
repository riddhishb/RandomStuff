

/*
 *  Written in AVR Studio 5
 *  Compiler: AVR GNU C Compiler (GCC)
 *
 *  Author: AVR Tutorials
 *  Website: www.AVR-Tutorials.com
*/
 
#include<avr/io.h>
 
int main()
{
	unsigned char temp;
	DDRB |= 1<<PINB0;			// Set PB0 as output
	ACSR = 0x00; 			// Configured the Analog Comparator
	while(1)
	{
		temp = ACSR;		// Get the values from ACSR
		temp &= 0x20;		// Isolate the ACO bit 
		if(temp & 0x20)		// Test if ACO is set
			PORTB &= ~0x01;	// Turn LED OFF  - if ACO = 1
		else
			PORTB |= 0x01;	// Turn LED ON - if ACO = 0
	}
	return 0;
}
