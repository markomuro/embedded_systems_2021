/*
 * gyro.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Lenovo T440
 */
#include "inttypes.h"
#include "gyro.h"
#include "main.h"
extern SPI_HandleTypeDef hspi5;


uint8_t Gyro_CanReadWHOAMI() {
	uint8_t pTxData[2] = {READ_SLAVE_OPERATION | REG_WHOAMI, 0}; //read register command
	uint8_t pRxData[2] = {0, 0};
    CS_START(); // Kasuta ja implementeeri, kui puudub riistvaraline CS
	HAL_SPI_TransmitReceive(&hspi5, pTxData, pRxData, 2, HAL_MAX_DELAY);
	CS_END(); // Kasuta ja implementeeri, kui puudub riistvaraline CS
	return pRxData[1] == REG_WHOAMI_DEFAULT_VALUE;
}

//gyro initsialiseerimine
void Gyro_Init(){
	uint8_t pTxData[4] = {WRITE_SLAVE_OPERATION | CTRL_REG1, ENABLE_GYRO, 0, DATA_READY_EN};
	uint8_t pRxData[4] = {0, 0, 0, 0};
	CS_START();
	HAL_SPI_TransmitReceive(&hspi5, pTxData, pRxData, 4, HAL_MAX_DELAY);
	CS_END();
}

//check if data ready on gyro
uint8_t Gyro_HasData(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_SET){
		return 1;
	}else return 0;
}

//read data from gyro over SPI
void Gyro_ReadXYZ(Gyro_xyz_data *ptr){
	uint8_t pTxData[2] = {READ_SLAVE_OPERATION | OUT_X_L, 0};
	uint8_t pRxData[7] = {0, 0, 0, 0, 0, 0, 0};
	CS_START();
	HAL_SPI_TransmitReceive(&hspi5, pTxData, pRxData, 7, HAL_MAX_DELAY);
	CS_END();
	ptr->x = (pRxData[2] << 8) | pRxData[1];
	ptr->y = (pRxData[4] << 8) | pRxData[3];
	ptr->z = (pRxData[6] << 8) | pRxData[5];

}



