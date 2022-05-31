/*
 * log.h
 *
 *  Created on: 2. okt 2021
 *      Author: Lenovo T440
 */

#ifndef INC_LOG_H_
#define INC_LOG_H_

#include "inttypes.h"
extern char puhver[100];

void _log_process_msg(char *msg, uint16_t len);

#define LOGLEVEL_OFF (99)
#define LOGLEVEL_TRACE (1)
#define LOGLEVEL_DEBUG (2)
#define LOGLEVEL_WARN (3)
#define LOGLEVEL_ERROR (4)

#define LOG_AT_LOG_LEVEL(LOGLEVEL, TYPE, FORMAT, ...) _log_process_msg(puhver, snprintf(puhver,sizeof(puhver),"%d:%s:%s:" FORMAT"\n", HAL_GetTick(),TYPE,__FILE__, ##__VA_ARGS__)); \
	if (LOGLEVEL == LOGLEVEL_ERROR) {HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);}
#define LOG_TRACE(FORMAT, ...) LOG_AT_LOG_LEVEL(LOGLEVEL_TRACE, "TRACE", FORMAT, ##__VA_ARGS__)
#define LOG_DEBUG(FORMAT, ...) LOG_AT_LOG_LEVEL(LOGLEVEL_DEBUG, "DEBUG", FORMAT, ##__VA_ARGS__)
#define LOG_WARNING(FORMAT, ...) LOG_AT_LOG_LEVEL(LOGLEVEL_WARN, "WARN", FORMAT, ##__VA_ARGS__)
#define LOG_ERROR(FORMAT, ...) LOG_AT_LOG_LEVEL(LOGLEVEL_ERROR, "ERROR", FORMAT, ##__VA_ARGS__)


#endif /* INC_LOG_H_ */
