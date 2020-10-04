/*
 * timer.c
 *
 *  Created on: 8 sie 2019
 *      Author: TomaszS
 */


#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"

void timeout_Init()
{
	TCNT0 = 0;
}
