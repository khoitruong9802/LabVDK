/*
 * software_timer.h
 *
 *  Created on: Oct 6, 2022
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;

void set_timer1(int duration);
void set_timer2(int duration);
void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
