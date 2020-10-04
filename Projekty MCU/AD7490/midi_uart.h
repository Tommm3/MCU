/*
 * midi_uart.h
 *
 *  Created on: 16 lis 2019
 *      Author: TomaszS
 */

#ifndef MIDI_UART_H_
#define MIDI_UART_H_

#define UART_BAUD 31250
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1)

// midi states
#define MIDI_WAIT 1
#define MIDI_READING 2
#define MIDI_IGNORING 3

// midi events
#define MIDI_NOTE_OFF 	0x80
#define MIDI_NOTE_ON 	0x90
#define MIDI_POLY_TOUCH 	0xa0
#define MIDI_CONTROL_CHANGE	0xb0
#define MIDI_PROGRAM_CHANGE	0xc0
#define MIDI_CHANNEL_TOUCH	0xd0
#define MIDI_PITCH_BEND	        0xe0

// midi system events
#define MIDI_SYSEX_START        0xF0
#define MIDI_SYSEX_END          0xF7
#define MIDI_MTC                0xF1
#define MIDI_SPP                0xF2
#define MIDI_SONG_SEL           0xF3
#define MIDI_TUNE_REQ           0xF6
#define MIDI_CLOCK              0xF8
#define MIDI_SYNC               0xF9
#define MIDI_START              0xFA
#define MIDI_STOP               0xFC
#define MIDI_CONT               0xFB
#define MIDI_SENSE              0xFE
#define MIDI_RESET              0xFF


#define MIDI_DATA_MASK			0x7F
#define MIDI_STATUS_MASK		0xF0
#define MIDI_CHANNEL_MASK		0x0F

void USART_Init( uint16_t ubrr);
void USART_Transmit( uint8_t data );
void USART_puts(char *s);
void USART_putint(int val);


#endif /* MIDI_UART_H_ */
