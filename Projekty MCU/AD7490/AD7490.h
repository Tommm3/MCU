/*
 * AD7490.h
 *
 *  Created on: 26 sty 2020
 *      Author: TomaszS
 */

#ifndef AD7490_H_
#define AD7490_H_

#define CREG_WRITE   0x800
#define CREG_SEQ     0x400
#define CREG_ADD3	 0x200
#define CREG_ADD2    0x100
#define CREG_ADD1    0x080
#define CREG_ADD0    0x040
#define CREG_PM1     0x020
#define CREG_PM0     0x010
#define CREG_SHADOW  0x008
#define CREG_WEAK    0x004
#define CREG_RANGE   0x002
#define CREG_CODING  0x001

#define    SPI spi;
 #define   DigitalOut cs;

    unsigned short readv(void);  // dummy read for triggering at sequential mode


    void AD7490(void);
//    AD7490(SPI _spi, PinName _cs);
//    virtual ~AD7490(){};

    unsigned short convertv(int ch);       // one shot conversion at channel [ch]
  //  void convert(short data[]);             // convert all (16) channels with one short conv.

    void sequential(int ch);   // start sequential mode from channel [0] to [ch]
 //   void read(short data[]);                // read [0] to [ch], and copy to user area

    void spi_init_master (void);
    void Wyslij_spi(char bajt);
    char Odbieraj_spi();
    unsigned char spi_tranceiver (unsigned char data);
    void adc_init(void);
    uint8_t get_adc(unsigned short channel);


#endif /* AD7490_H_ */
