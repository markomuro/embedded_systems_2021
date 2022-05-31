/*
 * button.c
 *
 *  Created on: 16. sept 2021
 *      Author: Lenovo T440
 */

#ifndef SRC_BUTTON_C_
#define SRC_BUTTON_C_
#include "button.h"
#include "gpio.h"

Button_State nupu_olek;
Button_State nupu_olek_previous = Button_Up;

Button_State Button_Update() {

	if (nupu_olek_previous == Button_Up && HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET){
		nupu_olek = Button_Up;
		nupu_olek_previous = Button_Up;
	}
	else if (nupu_olek_previous == Button_Down && HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET){
		nupu_olek = Button_Rising;
		nupu_olek_previous = Button_Up;
	}
	else if (nupu_olek_previous == Button_Up && HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET){
		nupu_olek = Button_Falling;
		nupu_olek_previous = Button_Down;
	}
	else if (nupu_olek_previous == Button_Down && HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET){
		nupu_olek = Button_Down;
		nupu_olek_previous = Button_Down;
	}
	return 0;
}

Button_State Button_GetState(){
	return nupu_olek;
}


#endif /* SRC_BUTTON_C_ */
