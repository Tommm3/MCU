/*
 * midi_uart.c
 *
 *  Created on: 16 lis 2019
 *      Author: TomaszS
 */

#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>
#include<string.h>

#include"midi_uart.h"

void USART_Init( uint16_t ubrr)
{
/* Set baud rate */
UBRRH = (uint8_t)(ubrr>>8);
UBRRL = (uint8_t)ubrr;
/* Enable receiver and transmitter */
UCSRB = (1<<RXEN)|(1<<TXEN);
/* Set frame format: 8data, 1stop bit */
UCSRC = (1<<URSEL)|(3<<UCSZ0);
}


void USART_Transmit( uint8_t data )
{
/* Wait for empty transmit buffer */
while ( !( UCSRA & (1<<UDRE)) );
/* Put data into buffer, sends the data */
UDR = data;
}

void USART_puts(char *s)
{
	while(*s) USART_Transmit(*s++);
}

void USART_putint(int val)
{
	char buf[7];
	itoa(val, buf, 10);
	USART_puts(buf);
}
