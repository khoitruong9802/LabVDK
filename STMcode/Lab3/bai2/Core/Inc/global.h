/*
 * global.h
 *
 *  Created on: Nov 16, 2022
 *      Author: DELL
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define MODE_BUTTON 0
#define INC_BUTTON 1
#define CONFIRM_BUTTON 2

#define INIT 1
#define MODE1 2
#define MODE2 3
#define MODE3 4
#define MODE4 5

extern int MODE;
extern int Execute_one_time;
extern int flag_Button_Mode_Released;
extern int flag_Button_Inc_Released;
extern int flag_Button_Confirm_Released;

extern int red_duration;
extern int yellow_duration;
extern int green_duration;

#endif /* GLOBAL_H_ */
