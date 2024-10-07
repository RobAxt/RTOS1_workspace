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
 * @file   : task_b.c
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
#define G_TASK_B_CNT_INI		0ul

#define TASK_B_TICK_DEL_MAX		(pdMS_TO_TICKS(2500ul))

/********************** internal data declaration ****************************/
/* Task B Flag */
bool task_b_flag;

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_task_b 					= "Task B - Output Gateway";

const char *p_task_b_wait_exit			= "  ==> Task    B - Wait:   Exit";
//const char *p_task_b_signal_continue	= "  ==> Task    B - Signal: Continue ==>";
const char *p_task_b_wait_counter       = "  ==> Task    B - Signal: Counter";
//const char *p_task_b_wait_mutex			= "  ==> Task    B - Wait:   Mutex";
//const char *p_task_b_signal_mutex		= "  ==> Task    B - Signal: Mutex    ==>";

//const char *p_task_b_g_tasks_cnt		= "  <=> Task    B - g_tasks_cnt:";

const char *p_task_b_wait_2500mS		= "  ==> Task    B - Wait:   2500mS";

/********************** external data declaration *****************************/
uint32_t g_task_b_cnt;

/********************** external functions definition ************************/
/* Task B thread */
void task_b(void *parameters)
{
	#if (TEST_X == TEST_0)

	g_task_b_cnt = G_TASK_B_CNT_INI;

	/*  Declare & Initialize Task Function variables for argument, led, button and task */
	char *p_task_name = (char *)pcTaskGetName(NULL);

	/* Print out: Application Update */
	LOGGER_LOG("  %s is running - %s\r\n", p_task_name, p_task_b);

    /* Reset Task B Flag */
    task_b_flag = false;
    SemaphoreHandle_t h_exit_bin_sem = (SemaphoreHandle_t) parameters;
    xSemaphoreTake(h_exit_bin_sem, (portTickType) 0);

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

		/* Update Task B Counter */
		g_task_b_cnt++;

		/* Print out: Wait Exit */
		LOGGER_LOG("  %s\r\n", p_task_b_wait_exit);
		xSemaphoreTake(h_exit_bin_sem, portMAX_DELAY);

		/* Print out: Wait Mutex */
		//LOGGER_LOG("  %s\r\n", p_task_b_wait_mutex);
		//xSemaphoreTake(h_mutex_mut_sem, portMAX_DELAY);
		/* Update Task A & B Counter */
		//g_tasks_cnt--;

		/* Print out: Task A & B Counter*/
		//LOGGER_LOG("  %s %d\r\n", p_task_b_g_tasks_cnt, (int)g_tasks_cnt);

		/* Check Task A & B Counter and Set Task B Flag */
		//if ((G_TASKS_CNT_MAX - 1) == g_tasks_cnt)
		//{
		/* Set Task B Flag */
		//	task_b_flag = true;
		//}

		/* Print out: Signal Mutex */
		//LOGGER_LOG("  %s\r\n", p_task_b_signal_mutex);
		//xSemaphoreGive(h_mutex_mut_sem);

		/* Check Task B Flag, Reset Task B Flag and Do it here */
		//if (true == task_b_flag)
		//{
			/* Reset Task B Flag */
		//	task_b_flag = false;

		LOGGER_LOG("  %s\r\n", p_task_b_wait_counter);
		xSemaphoreGive(h_counter_sem);

		/* Do it here */
		/* Print out: Signal Continue */
		//LOGGER_LOG("  %s\r\n", p_task_b_signal_continue);
		//xSemaphoreGive(h_continue_bin_sem);

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
