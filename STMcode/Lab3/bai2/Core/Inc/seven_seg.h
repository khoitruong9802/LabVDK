/*
 * seven_seg.h
 *
 *  Created on: Nov 7, 2022
 *      Author: DELL
 */

#ifndef INC_SEVEN_SEG_H_
#define INC_SEVEN_SEG_H_

#include "main.h"

#define MAX_LED 4

void display_7SEG(int num);
void update_7SEG(int index, int led_buffer[]);

#endif /* INC_SEVEN_SEG_H_ */
