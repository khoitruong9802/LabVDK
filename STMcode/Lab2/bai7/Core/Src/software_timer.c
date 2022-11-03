/*
 * software_timer.c
 *
 *  Created on: Oct 19, 2022
 *      Author: DELL
 */

#include "software_timer.h"

int timer0_flag = 0;
int timer0_counter = 0;

void set_timer0(int duration) {
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
}

void timer_run() {
	if (timer0_counter > 0) {
		timer0_counter--;
		if (timer0_counter <= 0) {
			timer0_flag = 1;
		}
	}
}
