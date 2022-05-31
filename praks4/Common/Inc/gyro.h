/*
 * gyro.h
 *
 *  Created on: Oct 28, 2021
 *      Author: Lenovo T440
 */

#ifndef INC_GYRO_H_
#define INC_GYRO_H_

typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
} Gyro_xyz_data;

uint8_t Gyro_CanReadWHOAMI();
void Gyro_Init();
uint8_t Gyro_HasData();
void Gyro_ReadXYZ(Gyro_xyz_data *ptr);

#define CTRL_REG1 0x20
#define OUT_X_L 0x28 // where X value low byte begins
#define ENABLE_GYRO 0b00001111 //enable xyz axes, ODR 95Hz, cut-off 12.5 - register value
#define DATA_READY_EN 0b00001000 // Data-ready on DRDY/INT2 register value
#define READ_SLAVE_OPERATION 0b11000000 // auto increment addr
#define WRITE_SLAVE_OPERATION 0b01000000 //auto increment address
#define REG_WHOAMI  0x0F //WHO_AM_I
#define REG_WHOAMI_DEFAULT_VALUE 0b11010100
// app note file says WHO_AM_I 0Fh 1 1 0 1 0 0 1 1 ???

#define CS_START() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET)
#define CS_END() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET)



#endif /* INC_GYRO_H_ */
