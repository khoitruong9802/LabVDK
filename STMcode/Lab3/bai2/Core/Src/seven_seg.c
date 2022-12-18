/*
 * seven_seg.c
 *
 *  Created on: Nov 7, 2022
 *      Author: DELL
 */

#include "seven_seg.h"
#include "software_timer.h"

unsigned char SEG[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
void display_7SEG(int num) {
	GPIOB->ODR = SEG[num];
}

void update_7SEG(int index, int led_buffer[]){
  switch (index){
	  case 0:
		  //Display the first 7SEG with led_buffer[0]
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, RESET);
		  display_7SEG(led_buffer[0]);
		  break;
	  case 1:
		  //Display the second 7SEG with led_buffer[1]
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, RESET);
		  display_7SEG(led_buffer[1]);
		  break;
	  case 2:
		  //Display the third 7SEG with led_buffer[2]
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, RESET);
		  display_7SEG(led_buffer[2]);
		  break;
	  case 3:
		  //Display the forth 7SEG with led_buffer[3]
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, SET);
		  display_7SEG(led_buffer[3]);
		  break;
	  default:
		  break;
  }
}