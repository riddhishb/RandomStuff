#include <stdlib.h>
#include <string.h>
#include <math.h> //include libm
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "lcd.h"
#include "lcd.c"

#include "adc.h"
#include "adc.c"

//#define UART_BAUD_RATE 2400
//#include "uart/uart.h"

#include "mq135.h"
#include "mq135.c"

//define mq135 pulldown resistor
#define MQ135_PULLDOWNRES 22000

int main(void) {
	LCD_CONTROL_DDR |= 1<<EN | 1<<RW | 1<<RS;
	_delay_ms(15);
	char printbuff[100];
	double d = 0;
	uint16_t adc = 0;

	//init uart
	//uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	//init adc
	adc_init();

	//init interrupt
	sei();

	long mq135_ro = 0;

	for (;;) {
		//uart_puts("reading...\r\n");
		Send_A_Command(0x01); //Clear Screen
		_delay_ms(2);
		Send_A_Command(0x38);
		_delay_us(50);
		Send_A_Command(0b00001110);
		_delay_us(50);

		//get adc
		adc = adc_read(0);

		//calculated resistence depends on the sensor pulldown resistor
		long res = adc_getresistence(adc, MQ135_PULLDOWNRES);
		//get ro
		mq135_ro = mq135_getro(res, MQ135_DEFAULTPPM);
		//convert to ppm (using default ro)
		d = mq135_getppm(res, MQ135_DEFAULTRO);

		//print adc
		//itoa(adc, printbuff, 10);
		//uart_puts("ADC     "); uart_puts(printbuff); uart_puts("\r\n");
		//Send_A_String("ADC = ");
		//Send_A_String(printbuff);

		//print resistance
		ltoa(res, printbuff, 10);
		//uart_puts("RES     "); uart_puts(printbuff); uart_puts("\r\n");
		//Send_A_Command(0xC0);
		Send_A_String("Res = ");
		Send_A_String(printbuff);
		_delay_ms(5000);

		//ltoa(mq135_ro, printbuff, 10);
		//uart_puts("ro      "); uart_puts(printbuff); uart_puts("\r\n");
		//Send_A_String("Ro = ");
		//Send_A_String(printbuff);

		dtostrf(d, 3, 5, printbuff);
		Send_A_Command(0xC0);
		Send_A_String("PPM = ");
		Send_A_String(printbuff);
		_delay_ms(5000);
		//uart_puts("ppm     "); uart_puts(printbuff); uart_puts("\r\n");

		//uart_puts("\r\n");

		//_delay_ms(1000);
	}
	
	return 0;
}
