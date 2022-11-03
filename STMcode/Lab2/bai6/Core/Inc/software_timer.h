/*
 * software_timer.h
 *
 *  Created on: Oct 19, 2022
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

//#define TIMER_CYCLE 10
extern int timer0_flag;

void set_timer0(int duration);
void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
