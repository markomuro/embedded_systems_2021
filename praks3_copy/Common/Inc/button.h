/*
 * button.h
 *
 *  Created on: 16. sept 2021
 *      Author: Lenovo T440
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_


typedef enum {
	Button_Up,
	Button_Rising,
	Button_Falling,
	Button_Down,
} Button_State;

Button_State Button_GetState();
Button_State Button_Update();

#endif /* INC_BUTTON_H_ */
