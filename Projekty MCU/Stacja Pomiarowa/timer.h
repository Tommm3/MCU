/*
 * timer.h
 *
 *  Created on: 8 sie 2019
 *      Author: TomaszS
 */

#ifndef TIMER_H_
#define TIMER_H_

#define TIMER_FLAG_RESET(){\
			TIFR |= _BV(TOV0);\
			TCNT0 = 0;\
		}
#define TIMER_FLAG_IS_SET TIFR & _BV(TOV0)
#define TENTH_SECOND_FLAG TCNT0 >= 195
#define TENTH_SECOND_FLAG_RESET TCNT0 = 0;

void timeout_Init(void);


#endif /* TIMER_H_ */
