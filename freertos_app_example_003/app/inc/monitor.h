/*
 * monitor.h
 *
 *  Created on: Oct 12, 2024
 *      Author: raxt
 */

#ifndef INC_MONITOR_H_
#define INC_MONITOR_H_
/********************** typedef **********************************************/
typedef struct
{
	char domain[8];
	char *task_Id;
	char dateTime[15];
} struct_q;
/********************** external functions declaration ***********************/
void monitor(void *parameters);

#endif /* INC_MONITOR_H_ */
