/*
 * monitor.c
 *
 *  Created on: Oct 12, 2024
 *      Author: raxt
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"
#include "cmsis_os.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "board.h"
#include "app.h"
#include "monitor.h"

/********************** external functions definition ************************/
/* Task monitor thread */
void monitor(void *parameters)
{
    struct_q item;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;;)
	{
		xQueueReceive(h_struct_q, &item, portMAX_DELAY);
	}

}
