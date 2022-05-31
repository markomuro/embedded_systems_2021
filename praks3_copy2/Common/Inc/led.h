/*
 * led.h
 *
 *  Created on: 16. sept 2021
 *      Author: Lenovo T440
 */

#ifndef INC_LED_H_
#define INC_LED_H_



#define LED_Green_Toggle() HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin)
#define LED_Green_Write(GPIO_PinState) HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET)
#define LED_Green_Read() HAL_GPIO_ReadPin(LD3_GPIO_Port, LD3_Pin)

#define LED_Red_Toggle() HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin)
#define LED_Red_Write(GPIO_PinState) HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET)
#define LED_Red_Read() HAL_GPIO_ReadPin(LD4_GPIO_Port, LD4_Pin)


#endif /* INC_LED_H_ */
