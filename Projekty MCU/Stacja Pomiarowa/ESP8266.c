/*
 * ESP8266.c
 *
 *  Created on: 26 sie 2019
 *      Author: TomaszS
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ESP8266.h"
#include "sht.h"

void send_temperature(uint8_t channel, float value)
{
	uint8_t integer = value;
	USART_puts("c:publish(\"michkrz/feeds/temperatura.czujnik");
	USART_putint(channel+1);
	USART_puts("\",\"");
	USART_putint(integer);
	USART_puts(".");
	float g = (value-integer)*10;
	USART_putint(g);
	USART_puts("\",0,0) \n");
}

void send_humidity(uint8_t channel, float value)
{
	uint8_t integer = value;
	USART_puts("c:publish(\"michkrz/feeds/wilgotnosc.czujnik");
	USART_putint(channel+1);
	USART_puts("\",\"");
	USART_putint(integer);
	USART_puts(".");
	float g = (value-integer)*10;
	USART_putint(g);
	USART_puts("\",0,0) \n");
}
