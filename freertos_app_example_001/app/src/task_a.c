/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @file   : task_a.c
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
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

/********************** macros and definitions *******************************/
#define G_TASK_A_CNT_INI		0ul

#define TASK_A_TICK_DEL_MAX		(pdMS_TO_TICKS(2500ul))

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_task_a				= "Task A - Gateway A";

const char *p_task_a_wait_entry_a	= "  ==> Task    A - Wait:   Entry_A";
const char *p_task_a_wait_exit_a	= "  ==> Task    A - Wait:   Exit_A";

const char *p_task_a_wait_mutex		= "  ==> Task    A - Wait:   Mutex";
const char *p_task_a_signal_mutex	= "  ==> Task    A - Signal: Mutex    ==>";

const char *p_task_a_wait_2500mS	= "  ==> Task    A - Wait:   2500mS";

/********************** external data declaration *****************************/
uint32_t g_task_a_cnt;

/********************** external functions definition ************************/
/* Task A thread */
void task_a(void *parameters)
{
	#if (TEST_X == TEST_0)

	g_task_a_cnt = G_TASK_A_CNT_INI;

	/*  Declare & Initialize Task Function variables for argument, led, button and task */
	char *p_task_name = (char *)pcTaskGetName(NULL);

	/* Print out: Application Update */
	LOGGER_LOG("  %s is running - %s\r\n", p_task_name, p_task_a);
	xSemaphoreTake(h_entry_a_bin_sem, (portTickType) 0);
	xSemaphoreTake(h_exit_a_bin_sem, (portTickType) 0);
	#endif

	#if (TEST_X == TEST_1)

	/* Here another code option */

	#endif

	#if (TEST_X == TEST_2)

	/* Here Chatbot Artificial Intelligence generated code */

	#endif

	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;;)
	{

		#if (TEST_X == TEST_0)

		/* Update Task A Counter */
		g_task_a_cnt++;

		/* Print out: Wait Entry A */
		LOGGER_LOG("  %s\r\n", p_task_a_wait_entry_a);
		xSemaphoreTake(h_entry_a_bin_sem, portMAX_DELAY);

		/* Print out: Wait Mutex */
		LOGGER_LOG("  %s\r\n", p_task_a_wait_mutex);
		xSemaphoreTake(h_mutex_mut_sem, portMAX_DELAY);

		/* Print out: Wait Exit A */
		LOGGER_LOG("  %s\r\n", p_task_a_wait_exit_a);
		xSemaphoreTake(h_exit_a_bin_sem, portMAX_DELAY);

		/* Print out: Signal Mutex */
		LOGGER_LOG("  %s\r\n", p_task_a_signal_mutex);
		xSemaphoreGive(h_mutex_mut_sem);

		/* Print out: Wait 2500mS */
//		LOGGER_LOG("  %s - %s %d\r\n", p_task_a_wait_2500mS, GET_NAME(g_task_a_cnt), (int)g_task_a_cnt);
		LOGGER_LOG("  %s\r\n", p_task_a_wait_2500mS);

		/* We want this task to execute every 2500 milliseconds. */
		vTaskDelay(TASK_A_TICK_DEL_MAX);

		#endif

		#if (TEST_X == TEST_1)

		/* Here another code option */

		#endif

		#if (TEST_X == TEST_2)

		/* Here Chatbot Artificial Intelligence generated code */

		#endif
	}
}

/********************** end of file ******************************************/
