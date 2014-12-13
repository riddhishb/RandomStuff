// Code for testing the PIR sensor with ATMEGA32
#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
DDRD |= 1 << PIND6;
DDRD &= ~(1 << PIND5);
PORTD |= 1 << PIND5;

while (1)
{
	//PORTD ^= 1 << PIND6;
if (bit_is_clear(PIND, 5))
{
	PORTD &= 0<<PIND6; //Fast
}
else
{
	PORTD |= 1<<PIND6; //Slow, from previous
}
}
}
