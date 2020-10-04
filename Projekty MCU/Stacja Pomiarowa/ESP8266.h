/*
 * ESP8266.h
 *
 *  Created on: 26 sie 2019
 *      Author: TomaszS
 */

#ifndef ESP8266_H_
#define ESP8266_H_


void send_temperature(uint8_t channel, float value);
void send_humidity(uint8_t channel, float value);

#endif /* ESP8266_H_ */
