/*
 * software_timer.c
 *
 *  Created on: Oct 6, 2022
 *      Author: DELL
 */

#include "software_timer.h"

int timer1_flag = 0;
int timer1_counter = 0;

int timer2_flag = 0;
int timer2_counter = 0;

void set_timer1(int duration) {
	timer1_counter = duration;
	timer1_flag = 0;
}

void set_timer2(int duration) {
	timer2_counter = duration;
	timer2_flag = 0;
}

void timer_run() {
	if (timer1_counter > 0) {
		timer1_counter--;
		if (timer1_counter <= 0) {
			//TODO
			timer1_flag = 1;
		}
	}
	if (timer2_counter > 0) {
		timer2_counter--;
		if (timer2_counter <= 0) {
			//TODO
			timer2_flag = 1;
		}
	}

}
