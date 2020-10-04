//
//  sht.c
//  avrSHT
//
//  Created by aercys on 10/08/16.
//  Copyright © 2016 aercys. All rights reserved.
//

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "sht.h"

void USART_Init( uint16_t ubrr);

void initialize_transmisson() {
    /*
     * SHT11
     * Start Sequence
     *        __    __
     * SCK  _|  |__|  |__
     *      __       ____
     * DATA   |_____|
     *
     */
    data_out();
    data_high;
    _delay_us(2);
    sck_high;
    _delay_us(2);
    data_low;
    _delay_us(2);
    sck_low;
    _delay_us(8);
    sck_high;
    _delay_us(2);
    data_high;
    _delay_us(2);
    sck_low;
}

void send_command(uint8_t command) {
    _delay_us(4);
    data_out();                               // Enable data as output port

    for (int i = 0; i < 8; i++) {
        if (0x01 & (command >> (7-i))) {
            data_high;
        } else {
            data_low;
        }

        _delay_us(4);
        sck_high;
        _delay_us(4);
        sck_low;
        
        if (i == 7) {
            data_in();
            data_high;

 //          while ((PINC & (1 << DATA)));

        }
    }
    
    _delay_us(4);
    sck_high;
    _delay_us(4);
    sck_low;
}

void reset() {
    data_out();
    data_high;
    
    for (int i = 0; i < 9; i++) {
        _delay_us(4);
        sck_high;
        _delay_us(4);
        sck_low;
    }
    initialize_transmisson();
}



uint16_t read_data() {
    uint8_t data_l, data_h;
    uint16_t measured;
    data_l = 0x00;
    data_h = 0x00;
    data_in();
    data_high;

    uint8_t bil=0;


    while(bil==0)
    {
    	static uint16_t i=0;
    	if(!(PINC & (1<<DATA)))
    	{
    		i=0;
    		bil=1;
    	}
    	else
    	{
    		i++;
    	}
    	if(i==50000)
    	{
    		i=0;
    		break;
    	}

    }

   // while (PINC & (1<<DATA));
    //Start receiving MSB
    receive_bytes(&data_h);
    ack(); // ack() to start getting LSB
    //Start receiving LSB
    receive_bytes(&data_l);
    
    if (bil == 0)
    {
    	measured = 0;
    }
    else
    {
    measured = (data_h << 8) | data_l;
    }
    return measured;
}

float calculate_measured_data(uint16_t measured_data, uint8_t value) {
    float _humidity, _temperature;
    
    switch (value) {
        case humidity:
            _humidity = measured_data * 0.0405 - 2.8 * pow(10, -6) * pow(measured_data, 2) - 4;
            return _humidity;
            break;
        case temperature:
            _temperature = -40.00 + 0.01 * measured_data;
            return _temperature;
            break;
    }
    
    return 1;
}

sht_data sht_sense() {
    float _temperature, _humidity;
    uint8_t temperature_int;
    uint16_t __humidity;
    sht_data data;
    initialize_transmisson();   // Initilize the sensor to send command
    send_command(temperature);
    _delay_us(80);              // Wait for measurement to complete
    _temperature = calculate_measured_data(read_data(), temperature);
    temperature_int = _temperature;
    if(temperature_int == 216)
    {
    	data._error = 1;
    	_temperature = 0;
    	_humidity = 0;
    }
    else
    {
    reset();
    send_command(humidity);
    _delay_us(80);
    __humidity = read_data();
    _humidity = calculate_measured_data(__humidity, humidity);
    _humidity = (_temperature - 25) * (0.01 + 0.00008 * __humidity) + _humidity;
    data._error = 0;
    }
    reset();
    data._temperature = _temperature;
    data._humidity = _humidity;
    _delay_ms(100);
    return data;
}


void USART_Init( uint16_t ubrr)
{
/* Set baud rate */
UBRRH = (uint8_t)(ubrr>>8);
UBRRL = (uint8_t)ubrr;
/* Enable receiver and transmitter */
UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
/* Set frame format: 8data, 2stop bit */
UCSRC = (1<<URSEL)|(3<<UCSZ0);
sei();
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


void receive_bytes(uint8_t *target) {
    for (int i = 0; i < 8; i++) {
        sck_high;
        _delay_us(4);
        if ((PINC & (1 << DATA))) {
            *target |= (1 << (7 - i));
        } else {
            *target &= ~(1 << (7 - i));
        }
        sck_low;
        _delay_us(4);
    }
}

void ack(void) {
    data_out();
    data_low;
    _delay_us(4);
    sck_high;
    _delay_us(4);
    sck_low;
    _delay_us(4);
    data_in();
    data_high;
}
