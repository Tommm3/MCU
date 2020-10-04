/*
 * pwm.c
 *
 *  Created on: 5 sie 2019
 *      Author: TomaszS
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pwm.h"

void RGB_Init()
{
	DDRB |= _BV(PB1) | _BV(PB2) | _BV(PB3);
	TCCR2 |= _BV(WGM21) | _BV(WGM20) | _BV(COM21) | _BV(CS22);
	TCCR1A |= _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
	TCCR1B |= _BV(WGM12) | _BV(CS11) | _BV(CS10);
	TIMSK |= _BV(TOIE0);
	TCNT0 = 177;
}
