//
//  sht.h
//  avrSHT
//
//  Created by aercys on 10/08/16.
//  Copyright © 2016 aercys. All rights reserved.
//

#ifndef sht_h
#define sht_h

// Commands for Measurement ------------------------------------------------------------------------------

#define temperature 0x03
#define humidity 0x05
#define soft_reset 0x1E

// Data and Clock Pin | Ports ----------------------------------------------------------------------------

#define SCK 5
#define DATA sda

// Data and Clock Modify Macros --------------------------------------------------------------------------

#define sck_high PORTB |= (1 << SCK)
#define sck_low PORTB &= ~(1 << SCK)
#define data_high PORTC |= (1 << DATA)
#define data_low PORTC &= ~(1 << DATA)
#define data_out(){ \
		DDRB |= (1 << SCK);\
		DDRC |= (1 << DATA);\
		}
#define data_in() {\
		DDRB |= (1 << SCK);\
		DDRC &= ~(1 << DATA);\
		}

//USART

#define UART_BAUD 9600
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1)

// SHT Data type
typedef struct {
    float _temperature;
    float _humidity;
    uint8_t _error;
} sht_data;

// USART

void USART_Init( uint16_t ubrr);
void USART_puts(char *s);
void USART_putint(int val);
uint8_t sda;

// Function prototypes -----------------------------------------------------------------------------------

void initialize_transmisson(void);
void send_command(uint8_t command);
void reset(void);
//void serial_init(void);
uint16_t read_data(void);
//void send_uart_char(unsigned char serial_data, FILE *stream);
float calculate_measured_data(uint16_t measured_data, uint8_t value);
void receive_bytes(uint8_t *target);
void ack(void);
sht_data sht_sense(void);

//FILE uart_output = FDEV_SETUP_STREAM(send_uart_char, NULL, _FDEV_SETUP_WRITE);

#endif /* sht_h */
