/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Created By: Riddhish Bhalodia

Refrences: Davide Gironi
	   Patrick Hood-Daniel

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DHT_H_
#define DHT_H_

#include <stdio.h>
#include <avr/io.h>

//setup port
#define DHT_DDR 	DDRB
#define DHT_PORT 	PORTB
#define DHT_PIN 	PINB
#define DHT_INPUTPIN 	PB0

//timeout retries
#define DHT_TIMEOUT 200

extern int8_t dht_gettemperature(int8_t *temperature);
extern int8_t dht_gethumidity(int8_t *humidity);
extern int8_t dht_gettemperaturehumidity(int8_t *temperature, int8_t *humidity);

#endif
