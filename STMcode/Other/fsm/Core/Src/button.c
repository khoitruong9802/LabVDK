/*
 * button.c
 *
 *  Created on: Oct 7, 2022
 *      Author: DELL
 */

#include "button.h"

int KeyReg0 = NORMAL_STATE;
int KeyReg1 = NORMAL_STATE;
int KeyReg2 = NORMAL_STATE;
int KeyReg3 = NORMAL_STATE;

int TimeOutForKeyPress =  100;
int button1_flag = 0;

int isButton1Pressed() {
	if (button1_flag == 1) {
		button1_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(){
	if(KeyReg3 == PRESSED_STATE){
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin); //Toggle LED
	}
}

void getKeyInput(){
  KeyReg2 = KeyReg1;
  KeyReg1 = KeyReg0;
  KeyReg0 = HAL_GPIO_ReadPin(); // Button Input
  if ((KeyReg1 == KeyReg0) && (KeyReg1 == KeyReg2)){
    if (KeyReg2 != KeyReg3){
      KeyReg3 = KeyReg2;

      if (KeyReg3 == PRESSED_STATE){
        TimeOutForKeyPress = 100;
        subKeyProcess();
      }
    } else {
       TimeOutForKeyPress --;
        if (TimeOutForKeyPress == 0){
          KeyReg3 = NORMAL_STATE;
        }
    }
  }
}
