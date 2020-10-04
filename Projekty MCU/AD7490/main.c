/*
 * main.c
 *
 *  Created on: 26 sty 2020
 *      Author: TomaszS
 */

#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>
#include<avr/interrupt.h>

#include"AD7490.h"
#include"midi_uart.h"

volatile uint16_t data;
volatile uint8_t charr;
volatile uint8_t tab[16];
volatile uint8_t check_dir[16];

uint8_t tab2[8];
uint8_t check_dir2[8];
volatile uint8_t k;

ISR(SPI_STC_vect)
{
	static uint8_t i=0;
	if (!i)
	{
	data = SPDR;
	i=1;
	}
	else
	{
	data <<= 8;
	data |= SPDR;
	data >>= 4;
	charr = data;
	charr >>=1;
	if (charr>121)
	{
		charr=121;
	}

	if((((check_dir[k] == 0) && (tab[k] < charr)) || ((check_dir[k] == 1) && (tab[k] < (charr-1)))))
	{
		PORTD ^= _BV(PD2);
		tab[k] = charr;
		if (check_dir[k] == 1)
		{
			check_dir[k] = 0;
		}
		USART_Transmit(MIDI_CONTROL_CHANGE);
		USART_Transmit(0x20+k);
		USART_Transmit(127-tab[k]*1.042);
//		USART_putint(k);
//		USART_puts(": ");
//		USART_putint(127-tab[k]*0.525);
//		USART_puts("\n");
//		PORTB &=~_BV(PB0);
	}
	else if ((((check_dir[k] == 1) && (tab[k] > charr)) || ((check_dir[k] == 0) && (tab[k] > (charr+1)))))
	{
		PORTD ^= _BV(PD2);
		tab[k] = charr;
		if (check_dir[k] == 0)
		{
			check_dir[k] = 1;
		}
		USART_Transmit(MIDI_CONTROL_CHANGE);
		USART_Transmit(0x20+k);
		USART_Transmit(127-tab[k]*1.042);
	}
	i=0;
	}
}

int main() {

	DDRB |= _BV(PB0);
	DDRD |= _BV(PD2);
	adc_init();
	spi_init_master();
	sei();
	_delay_ms(10);

    AD7490();

	USART_Init(__UBRR);
	PORTB |= _BV(PB0);

    while(1) {
    int a;

    for(k=0; k<16; k++)
    {
    unsigned short bang = convertv(k);
    _delay_ms(1);
    }

    for(a=0; a<8; a++)
    {
    uint8_t adc = get_adc(a);
    	if (((check_dir2[a] == 0) && (tab2[a] < adc)) || ((check_dir2[a] == 1) && (tab2[a] < (adc-1))))
    	{
    		if (check_dir2[a] == 1)
    		{
    			check_dir2[a] = 0;
    		}
    		PORTD ^= _BV(PD2);
    		tab2[a] = adc;
    //		USART_putint(a);
    //		USART_puts(": ");
    //		USART_putint(127- tab2[a]);
    //		USART_puts("\n");

    		USART_Transmit(MIDI_CONTROL_CHANGE);
    		USART_Transmit(0x50+a);
    		USART_Transmit(127- tab2[a]);
    //		PORTB &=~_BV(PB0);
    	}
    	else if (((check_dir2[a] == 1) && (tab2[a] > adc)) || ((check_dir2[a] == 0) && (tab2[a] > (adc+1))))
    	{
    		if (check_dir2[a] == 0)
    		{
    			check_dir2[a] = 1;
    		}
    		PORTD ^= _BV(PD2);
    		tab2[a] = adc;

    		USART_Transmit(MIDI_CONTROL_CHANGE);
    		USART_Transmit(0x50+a);
    		USART_Transmit(127- tab2[a]);
    	}
    }
  //  USART_puts("\n");


//        for(int i=0; i<32; i++)


    }
}
