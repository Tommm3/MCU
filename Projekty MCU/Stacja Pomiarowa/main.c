/*
 * main.c
 *
 *  Created on: 5 sie 2019
 *      Author: TomaszS
 */

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "sht.h"
#include "pwm.h"
#include "timer.h"
#include "ESP8266.h"

volatile uint8_t x_odb;
volatile uint8_t connected = 0;
volatile uint16_t second = 0;
volatile uint8_t STEP = 0;

ISR (TIMER0_OVF_vect)    // Timer1 ISR
{
	static uint8_t hundredth_second = 0;
	if(hundredth_second == 100)
	{
		hundredth_second = 0;
		second++;
	}
	TCNT0 = 177;   // for 1 sec at 16 MHz
	hundredth_second++;
}

ISR(USART_RXC_vect)
{
	x_odb = UDR;

	if(x_odb != '\n' )
	{
		if (x_odb == '%')
		{
			STEP = 2;
			connected = 0;
		}

		if (x_odb == '@')
		{
			connected = 1;
		}

	}


}


int main(void) {
    _delay_us(11);                  // Wait for sensor initialization
	USART_Init(__UBRR);
	RGB_Init();

    while (1) {
        sht_data data;

        switch (STEP) {
			case 0:
				TIMER_START;
				R = 220;
				G = 100;
				B = 0;
				if(second >= 60)
				{
					TIMER_STOP;
					second = 0;
					STEP = 2;
				}

				if (connected)
				{
					TIMER_STOP;
					second = 0;
					_delay_ms(500);
					STEP = 1;
				}
				break;
			case 1:
				G = 200;
				R = 0;
				B = 0;
	        	for(uint8_t i=0; i<6; i++)
	        	{
	        		sda=i;
	        		data = sht_sense();
	        		send_temperature(i, (float)data._temperature);
	        		_delay_ms(600);
	        		send_humidity(i, (float)data._humidity);
	        		_delay_ms(600);
	        	}
	        	TIMER_START;
	        	STEP = 3;
				break;
			case 2:
				G = 0;
				R = 200;
				B = 0;

				_delay_ms(5000);
				USART_puts("node.restart()\n");
				STEP = 0;
				break;
			case 3:
				if(connected == 0)
				{
					STEP = 2;
				}

				G = 0;
				R = 0;
				B = 200;

				if(second >= 600)
				{
					TIMER_STOP;
					second = 0;
					STEP = 1;
				}
				break;
			default:
				break;
		}




    }

    return 0; // never reached
}


