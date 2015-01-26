#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
DDRD |= 0xFF;
TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0; // Page No. 108
TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10; // Page No. 110
ICR1 = 19999;
OCR1A = ICR1 - 2000; //18000

while (1)
{
}
}
