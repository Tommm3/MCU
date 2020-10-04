/*
 * AD7490.c
 *
 *  Created on: 26 sty 2020
 *      Author: TomaszS
 */

#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>
#include"AD7490.h"

void AD7490(void)

{
    unsigned short x = 0;

    unsigned char higherByte, lowerByte;

    for(int i=0; i<3; i++){

        x = 0;
        x |= CREG_WRITE;
    //    x |= CREG_SEQ;
    //    x |= CREG_SHADOW;
        x |= CREG_ADD3;
        x |= CREG_ADD2;
        x |= CREG_ADD1;
        x |= CREG_ADD0;
        x |= CREG_PM1;
        x |= CREG_PM0;
    //    x |= CREG_RANGE;
        x |= CREG_CODING;

        higherByte = (unsigned char)(((x<<4) & 0xff00) >> 8);
        lowerByte = (unsigned char)((x<<4) & 0x00ff);

        PORTB &=~_BV(PB2);
        Wyslij_spi(higherByte);
        Wyslij_spi(lowerByte);
        PORTB |=_BV(PB2);

//        printf("INIT: send = 0x%X, ret = 0x%X\n", x, ret);
    }
}

unsigned short convertv(int ch)
{
    unsigned short x = 0;

    unsigned char higherByte, lowerByte;

    x |= CREG_WRITE;
//    x |= CREG_SEQ;
//    x |= CREG_SHADOW;
//    x |= CREG_ADD3;
//    x |= CREG_ADD2;
//    x |= CREG_ADD1;
    x |= (CREG_ADD0|CREG_ADD1|CREG_ADD2|CREG_ADD3) & (ch<<6);

    x |= CREG_PM1;
    x |= CREG_PM0;
    x |= CREG_RANGE;
    x |= CREG_CODING;

    higherByte = (unsigned char)(((x<<4) & 0xff00) >> 8);
    lowerByte = (unsigned char)((x<<4) & 0x00ff);

    PORTB &=~_BV(PB2);

	SPDR = higherByte;
	while(!(SPSR & (1<<SPIF)));

	SPDR = lowerByte;
	while(!(SPSR & (1<<SPIF)));

    unsigned short ret = SPDR;
    PORTB |=_BV(PB2);

//    printf("send = 0x%X, ch = %2d, ret = %d\n", x, (ret>>12)&0xF, ret&0xFFF);

    return ret;
}

void convert(short data[])
{
    for(int ch=0; ch<16; ch++) data[ch]=0;
    for(int ch=0; ch<16; ch++){
        unsigned short ret = convertv(ch);

        data[ ret>>12&0xF ] = ret&0xFFF;
    }
}


void sequential(int ch)
{
    unsigned short x = 0;

    x |= CREG_WRITE;
    x |= CREG_SEQ;
    x |= CREG_SHADOW;
//    x |= CREG_ADD3;
//    x |= CREG_ADD2;
//    x |= CREG_ADD1;
    x |= (CREG_ADD0|CREG_ADD1|CREG_ADD2|CREG_ADD3) & (ch<<6);

    x |= CREG_PM1;
    x |= CREG_PM0;
    x |= CREG_RANGE;
    x |= CREG_CODING;

    PORTB &=~_BV(PB2);
    Wyslij_spi(x<<4);
    PORTB |=_BV(PB2);
}



unsigned short readv(void)
{
//    unsigned short x = 0;

//    x |= CREG_WRITE;
//    x |= CREG_SEQ;
//    x |= CREG_SHADOW;
//    x |= CREG_ADD3;
//    x |= CREG_ADD2;
//    x |= CREG_ADD1;
//    x |= (CREG_ADD0|CREG_ADD1|CREG_ADD2|CREG_ADD3) & (ch<<6);

//    x |= CREG_PM1;
//    x |= CREG_PM0;
//    x |= CREG_RANGE;
//    x |= CREG_CODING;

	PORTB &=~_BV(PB2);
    unsigned short ret = Odbieraj_spi();
    PORTB |=_BV(PB2);

//    printf("send = 0x%X, ch = %2d, ret = %d\n", x, (ret>>12)&0xF, ret&0xFFF);

    return ret;
}

//void read(short data[])
//{
 //   for(int ch=0; ch<16; ch++) data[ch]=0;
  //  for(int ch=0; ch<16; ch++){
   //     unsigned short ret = readv();
//
   //     data[ ret>>12&0xF ] = ret&0xFFF;
  //  }
//}

void spi_init_master (void)
{
    // Set MOSI, SCK as Output
    DDRB=(1<<5)|(1<<3)|(1<<2);

    // Enable SPI, Set as Master
    // Prescaler: Fosc/16, Enable Interrupts
    //The MOSI, SCK pins are as per ATMega8

   SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPIE)|(1<<SPR0);

 // Enable Global Interrupts
 //sei();
}

void Wyslij_spi(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	cData = SPDR;

}

char Odbieraj_spi()
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return data register */
	return SPDR;
}

unsigned char spi_tranceiver (unsigned char data)
{
    SPDR = data;                       //Load data into the buffer
    while(!(SPSR & (1<<SPIF) ));       //Wait until transmission complete
    return(SPDR);                      //Return received data
}

void adc_init(void)
{
	ADCSRA = 1<<ADEN | 1<<ADPS0 | 1<<ADPS2;
	ADMUX |= (1<<REFS1) | (1<<REFS0) | (1<<ADLAR);
}

uint8_t get_adc(unsigned short channel)
{
	unsigned short adc;

	ADMUX = (1<<REFS1) | (1<<REFS0) | (1<<ADLAR);

	ADMUX |= channel;

	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	adc = ADCH;
	adc>>=1;

	return adc;
}
