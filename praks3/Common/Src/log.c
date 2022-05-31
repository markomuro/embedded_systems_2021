/*
 * log.c
 *
 *  Created on: 2. okt 2021
 *      Author: Lenovo T440
 */

#include "log.h"
#include "inttypes.h"
#include "usbd_cdc_if.h"

char puhver[100];

void _log_process_msg(char *msg, uint16_t len){
	CDC_Transmit_HS(msg, len);
	HAL_Delay(10); //HTerm won't be fast enough

}
