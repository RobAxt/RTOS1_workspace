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
/* Task A Flag */
//bool task_a_flag;

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_task_a				= "Task A - Input Gateway";

const char *p_task_a_wait_entry		= "  ==> Task    A - Wait:   Entry";
//const char *p_task_a_wait_continue	= "  ==> Task    A - Wait:   Continue";
const char *p_task_a_wait_counter   = "  ==> Task    A - Wait:   Counter";
//const char *p_task_a_wait_mutex		= "  ==> Task    A - Wait:   Mutex";
//const char *p_task_a_signal_mutex	= "  ==> Task    A - Signal: Mutex    ==>";

//const char *p_task_a_g_tasks_cnt	= "  <=> Task    A - g_tasks_cnt:";

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
	task_config_t* task_config = (task_config_t*) parameters;
	char *p_task_name = (char *)pcTaskGetName(NULL);
	char vBuffer[8] = {0};
	/* Print out: Application Update */
	LOGGER_LOG("  %s is running - %s\r\n", p_task_name, p_task_a);

    /* Init Task A & B Counter and Reset Task A Flag */
//	g_tasks_cnt = G_TASKS_CNT_INI;
//    task_a_flag = false;

	//    xSemaphoreTake(h_entry_bin_sem, (portTickType) 0);
	//	xSemaphoreTake(h_continue_bin_sem, (portTickType) 0);
	
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

		/* Print out: Wait Entry */
		LOGGER_LOG("  %s\r\n", p_task_a_wait_entry);
		//xSemaphoreTake(h_entry_bin_sem, portMAX_DELAY);
		xQueueReceive(task_config->h_q, &vBuffer, portMAX_DELAY);
		LOGGER_LOG("  New Car Arrived: %s \r\n", vBuffer);

		LOGGER_LOG("  %s\r\n", p_task_a_wait_counter);
		xSemaphoreTake(task_config->h_counter_sem, portMAX_DELAY);
		LOGGER_LOG("Car parked and there was a free slot: %s \r\n", vBuffer);
		/* Do it here */
		/* Print out: Wait Continue */
		//LOGGER_LOG("  %s\r\n", p_task_a_wait_continue);
		//xSemaphoreTake(h_continue_bin_sem, portMAX_DELAY);


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
