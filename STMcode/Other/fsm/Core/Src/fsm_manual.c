/*
 * fsm_manual.c
 *
 *  Created on: Oct 7, 2022
 *      Author: DELL
 */

#include "fsm_manual.h"

void fsm_manual_run() {
	switch (status) {
		case MAN_RED:
			//TODO
			if (timer1_flag == 1) {
				status = AUTO_RED;
				set_timer1(5000);
			}
			if (button1_flag == 1) {
				status = MAN_GREEN;
				set_timer1(10000);
			}
			break;
		case AUTO_RED:
			if (timer1_flag == 1) {
				status = AUTO_GREEN;
				set_timer1(3000);
			}
			if (button1_flag == 1) {
				button1_flag == 0;
				status = MAN_RED;
				set_timer1(10000);
			}
			break;
		default:
			break;
	}
}
