/*
 * software_timer.c
 *
 *  Created on: Oct 7, 2022
 *      Author: DELL
 */

#include "software_timer.h"

int timer1_flag = 0;
int timer1_counter = 0;

void set_timer1(int duration) {
	timer1_counter = duration;
	timer1_flag = 0;
}

void clear_timer1() {
	set_timer1(0);
}

void timer_run() {
	if (timer1_counter > 0) {
		timer1_counter--;
		if (timer1_counter <= 0) {
			timer1_flag = 1;
		}
	}
}
