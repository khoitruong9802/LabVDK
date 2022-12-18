/*
 * input_processing.c
 *
 *  Created on: Nov 16, 2022
 *      Author: DELL
 */

#include "main.h"
#include "input_reading.h"
#include "seven_seg.h"
#include "global.h"
#include "software_timer.h"

void set_traffic1(int R, int Y, int G) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, R);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, Y);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, G);
}

void set_traffic2(int R, int Y, int G) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, R);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, Y);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, G);
}

enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};
enum ButtonState Button_Mode_State = BUTTON_RELEASED;
enum ButtonState Button_Inc_State = BUTTON_RELEASED;
enum ButtonState Button_Confirm_State = BUTTON_RELEASED;

void fsm_for_input_processing(void) {
	switch (Button_Mode_State) {
	case BUTTON_RELEASED:
		if (is_button_pressed(MODE_BUTTON)) {
			Button_Mode_State = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!(is_button_pressed(MODE_BUTTON))) {
			Button_Mode_State = BUTTON_RELEASED;
		} else {
			if (is_button_pressed_1s(MODE_BUTTON)) {
				Button_Mode_State = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if (!(is_button_pressed(MODE_BUTTON))) {
			Button_Mode_State = BUTTON_RELEASED;
		}
		break;
	default:
		break;
	}
	switch (Button_Inc_State) {
		case BUTTON_RELEASED:
			if (is_button_pressed(INC_BUTTON)) {
				Button_Inc_State = BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:
			if (!(is_button_pressed(INC_BUTTON))) {
				Button_Inc_State = BUTTON_RELEASED;
			} else {
				if (is_button_pressed_1s(INC_BUTTON)) {
					Button_Inc_State = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!(is_button_pressed(INC_BUTTON))) {
				Button_Inc_State = BUTTON_RELEASED;
			}
			break;
		default:
			break;
		}
	switch (Button_Confirm_State) {
		case BUTTON_RELEASED:
			if (is_button_pressed(CONFIRM_BUTTON)) {
				Button_Confirm_State = BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:
			if (!(is_button_pressed(CONFIRM_BUTTON))) {
				Button_Confirm_State = BUTTON_RELEASED;
			} else {
				if (is_button_pressed_1s(CONFIRM_BUTTON)) {
					Button_Confirm_State = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!(is_button_pressed(CONFIRM_BUTTON))) {
				Button_Confirm_State = BUTTON_RELEASED;
			}
			break;
		default:
			break;
		}
}

int red_duration = 5;
int yellow_duration = 2;
int green_duration = 3;

int led_buffer[MAX_LED] = {0, 0, 0, 0};
int index_led = 0;
int counter_for_traffic1 = 5, counter_for_traffic2 = 3;
int traffic1_state = 0, traffic2_state = 1;

void display_traffic_light() {
	if (timer2_flag == 1) {
		set_timer2(1000);
		counter_for_traffic1--;
		counter_for_traffic2--;
	}
	if (counter_for_traffic2 == 0) {
		if (traffic2_state == 0) {
			counter_for_traffic2 = green_duration;
		} else if (traffic2_state == 1) {
			counter_for_traffic2 = yellow_duration;
		} else {
			counter_for_traffic2 = red_duration;
		}
		traffic2_state = (traffic2_state + 1) % 3;
	}
	if (traffic1_state == 0) {
		set_traffic1(1, 0, 0);
	} else if (traffic1_state == 1) {
		set_traffic1(0, 0, 1);
	} else {
		set_traffic1(0, 1, 0);
	}
	if (traffic2_state == 0) {
		set_traffic2(1, 0, 0);
	} else if (traffic2_state == 1) {
		set_traffic2(0, 0, 1);
	} else {
		set_traffic2(0, 1, 0);
	}
	if (counter_for_traffic1 == 0) {
		if (traffic1_state == 0) {
			counter_for_traffic1 = green_duration;
		} else if (traffic1_state == 1) {
			counter_for_traffic1 = yellow_duration;
		} else {
			counter_for_traffic1 = red_duration;
		}
		traffic1_state = (traffic1_state + 1) % 3;
	}
	led_buffer[0] = counter_for_traffic2 / 10;
	led_buffer[1] = counter_for_traffic2 % 10;
	led_buffer[2] = counter_for_traffic1 / 10;
	led_buffer[3] = counter_for_traffic1 % 10;
}

void fsm_mode(void) {
	switch (MODE) {
		case INIT:
			set_timer0(125);
			set_timer1(125);
			set_timer2(1000);
			MODE = MODE1;
			break;
		case MODE1:
			if (Button_Mode_State == BUTTON_PRESSED && flag_Button_Mode_Released == 1) {
				flag_Button_Mode_Released = 0;
				Execute_one_time = 1;
				set_timer0(500);
				MODE = MODE2;
			}
			if (Button_Mode_State == BUTTON_RELEASED) {
				flag_Button_Mode_Released = 1;
			}
			display_traffic_light();
			if (Execute_one_time-- <= 0) {
				break;
				// Execute one time below this code
			}
			break;
		case MODE2:
			if (Button_Mode_State == BUTTON_PRESSED && flag_Button_Mode_Released == 1) {
				flag_Button_Mode_Released = 0;
				Execute_one_time = 1;
				set_timer0(500);
				MODE = MODE3;
			}
			if (Button_Mode_State == BUTTON_RELEASED) {
				flag_Button_Mode_Released = 1;
			}
			led_buffer[1] = 2;
			led_buffer[2] = red_duration / 10;
			led_buffer[3] = red_duration % 10;
			if (timer0_flag == 1) {
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, RESET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
				set_timer0(500);
			}
			////
			if (Button_Inc_State == BUTTON_PRESSED && flag_Button_Inc_Released == 1) {
				flag_Button_Inc_Released = 0;
				red_duration++;
			}
			if (Button_Inc_State == BUTTON_RELEASED) {
				flag_Button_Inc_Released = 1;
			}
			if (Button_Confirm_State == BUTTON_PRESSED) {
				MODE = MODE1;
			}
			////
			if (Execute_one_time-- <= 0) {
				break;
				// Execute one time below this code
			}
			break;
		case MODE3:
			if (Button_Mode_State == BUTTON_PRESSED && flag_Button_Mode_Released == 1) {
				flag_Button_Mode_Released = 0;
				Execute_one_time = 1;
				set_timer0(500);
				MODE = MODE4;
			}
			if (Button_Mode_State == BUTTON_RELEASED) {
				flag_Button_Mode_Released = 1;
			}
			led_buffer[1] = 3;
			led_buffer[2] = yellow_duration / 10;
			led_buffer[3] = yellow_duration % 10;
			if (timer0_flag == 1) {
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
				set_timer0(500);
			}
			////
			if (Button_Inc_State == BUTTON_PRESSED && flag_Button_Inc_Released == 1) {
				flag_Button_Inc_Released = 0;
				yellow_duration++;
			}
			if (Button_Inc_State == BUTTON_RELEASED) {
				flag_Button_Inc_Released = 1;
			}
			if (Button_Confirm_State == BUTTON_PRESSED) {
				MODE = MODE1;
			}
			////
			if (Execute_one_time-- <= 0) {
				break;
				// Execute one time below this code
			}
			break;
		case MODE4:
			if (Button_Mode_State == BUTTON_PRESSED && flag_Button_Mode_Released == 1) {
				flag_Button_Mode_Released = 0;
				Execute_one_time = 1;
				set_timer0(500);
				MODE = MODE1;
			}
			if (Button_Mode_State == BUTTON_RELEASED) {
				flag_Button_Mode_Released = 1;
			}
			led_buffer[1] = 4;
			led_buffer[2] = green_duration / 10;
			led_buffer[3] = green_duration % 10;
			if (timer0_flag == 1) {
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, RESET);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
				set_timer0(500);
			}
			////
			if (Button_Inc_State == BUTTON_PRESSED && flag_Button_Inc_Released == 1) {
				flag_Button_Inc_Released = 0;
				green_duration++;
			}
			if (Button_Inc_State == BUTTON_RELEASED) {
				flag_Button_Inc_Released = 1;
			}
			if (Button_Confirm_State == BUTTON_PRESSED) {
				MODE = MODE1;
			}
			////
			if (Execute_one_time-- <= 0) {
				break;
				// Execute one time below this code
			}
			break;
		default:
			break;
	}
	if (timer1_flag == 1) {
	  set_timer1(125);
	  //TODO
	  if (index_led >= MAX_LED) {
		  index_led = 0;
	  }
	  update_7SEG(index_led++, led_buffer);
	}
}
