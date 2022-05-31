/*
 * joystick.h
 *
 *  Created on: Nov 18, 2021
 *      Author: Lenovo T440
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

typedef struct {
	uint16_t x;
	uint16_t y;
} joy_data;


#define input_start_x 3600    // The lowest number of the range input.
#define input_end_x 310    // The largest number of the range input.
#define input_start_y 3700    // The lowest number of the range input.
#define input_end_y 580    // The largest number of the range input.
#define output_start_x 20 // The lowest number of the range output.
#define output_end_x 240  // The largest number of the range output
#define output_start_y 10 // The lowest number of the range output.
#define output_end_y 280  // The largest number of the range output
#define slope_x 1.0 * (output_end_x - output_start_x) / (input_end_x - input_start_x)
#define slope_y 1.0 * (output_end_y - output_start_y) / (input_end_y - input_start_y)


void map_numbers(joy_data *ptr1, joy_data *ptr2);
void Joy_Read(joy_data *ptr);

#define CS_START() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET)
#define CS_END() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET)

#define CH3 0b00011000 //register value for reading ch3
#define CH4 0b00100000 //register value for reading ch4

#endif /* INC_JOYSTICK_H_ */
