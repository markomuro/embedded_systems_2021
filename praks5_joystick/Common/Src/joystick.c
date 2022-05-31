/*
 * joystick.c
 *
 *  Created on: Nov 18, 2021
 *      Author: Lenovo T440
 */
#include "inttypes.h"
#include "joystick.h"
#include "main.h"

extern SPI_HandleTypeDef hspi4;

//read data from joystick adc over SPI
void Joy_Read(joy_data *ptr){
	uint8_t pTxData[1] = {CH3};
	uint8_t pRxData[2] = {0, 0};
	CS_START();
	HAL_SPI_TransmitReceive(&hspi4, pTxData, pRxData, 2, HAL_MAX_DELAY);
	CS_END();
	ptr->x = (pRxData[0] << 8) | pRxData[1];

	uint8_t pTxDataa[1] = {CH4};
	uint8_t pRxDataa[2] = {0, 0};
	CS_START();
	HAL_SPI_TransmitReceive(&hspi4, pTxDataa, pRxDataa, 2, HAL_MAX_DELAY);
	CS_END();
	ptr->y = (pRxDataa[0] << 8) | pRxDataa[1];

}

void map_numbers(joy_data *ptr1, joy_data *ptr2) {
	ptr2->x = output_start_x + slope_x * (ptr1->x - input_start_x);
	ptr2->y = output_start_y + slope_y * (ptr1->y - input_start_y);

}
