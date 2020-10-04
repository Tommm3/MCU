/*
 * pwm.h
 *
 *  Created on: 5 sie 2019
 *      Author: TomaszS
 */

#ifndef PWM_H_
#define PWM_H_

#define B OCR2
#define R OCR1A
#define G OCR1B

#define TIMER_START	TCCR0 |= _BV(CS02) | _BV(CS00)
#define TIMER_STOP TCCR0 = 0



void RGB_Init();

#endif /* PWM_H_ */
