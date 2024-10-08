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
 * @file   : app.c
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
#include "app.h"
#include "board.h"
#include "task_a.h"
#include "task_b.h"
#include "task_test.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_sys	= " RTOS - Event-Triggered Systems (ETS)\r\n";
const char *p_app	= " freertos_app_example_002: Parking lot\r\n";

/********************** external data declaration *****************************/
/* Task A & B Counter */
//uint32_t	g_tasks_cnt;
task_config_t task_config[] = { {NULL, NULL},{NULL, NULL},{NULL, NULL},{NULL, NULL} };

/* Declare a variable of type QueueHandle_t. This is used to reference queues*/
/* This is used to send messages from the Button task to the Led task. */

QueueHandle_t h_entry1_q;
QueueHandle_t h_entry2_q;
QueueHandle_t h_exit1_q;
QueueHandle_t h_exit2_q;

/* Declare a variable of type SemaphoreHandle_t (binary or counting) or mutex.
 * This is used to reference the semaphore that is used to synchronize a thread
 * with other thread or to ensure mutual exclusive access to...*/
//SemaphoreHandle_t h_entry_bin_sem;
//SemaphoreHandle_t h_exit1_bin_sem;
//SemaphoreHandle_t h_exit2_bin_sem;
//SemaphoreHandle_t h_continue_bin_sem;

//SemaphoreHandle_t h_mutex_mut_sem;

SemaphoreHandle_t h_counter1_sem;
SemaphoreHandle_t h_counter2_sem;

/* Declare a variable of type TaskHandle_t. This is used to reference threads. */
TaskHandle_t h_task_a;
TaskHandle_t h_task_aa;
TaskHandle_t h_task_b;
TaskHandle_t h_task_bb;
TaskHandle_t h_task_test;

/********************** external functions definition ************************/
void app_init(void)
{
	/* Print out: Application Initialized */
	LOGGER_LOG("\r\n");
	LOGGER_LOG("%s is running - Tick [mS] = %d\r\n", GET_NAME(app_init), (int)xTaskGetTickCount());

	LOGGER_LOG(p_sys);
	LOGGER_LOG(p_app);

    /* Before a queue or semaphore (binary or counting) or mutex is used it must 
     * be explicitly created */
	//vSemaphoreCreateBinary(h_entry_bin_sem);
	//vSemaphoreCreateBinary(h_exit1_bin_sem);
	//vSemaphoreCreateBinary(h_exit2_bin_sem);
	//vSemaphoreCreateBinary(h_continue_bin_sem);
	h_entry1_q = xQueueCreate( 2, sizeof("AB123YZ"));
	h_entry2_q = xQueueCreate( 2, sizeof("AB123YZ"));
	h_exit1_q = xQueueCreate( 2, sizeof("AB123YZ"));
	h_exit2_q = xQueueCreate( 2, sizeof("AB123YZ"));
//	h_mutex_mut_sem = xSemaphoreCreateMutex();

	h_counter1_sem = xSemaphoreCreateCounting(G_TASKS_CNT_MAX, G_TASKS_CNT_INI);
	h_counter2_sem = xSemaphoreCreateCounting(G_TASKS_CNT_MAX, G_TASKS_CNT_INI);

    /* Check the queue or semaphore (binary or counting) or mutex was created 
     * successfully. */
	//configASSERT(NULL != h_entry_bin_sem);
	//configASSERT(NULL != h_exit1_bin_sem);
	//configASSERT(NULL != h_exit2_bin_sem);
	//configASSERT(NULL != h_continue_bin_sem);
	configASSERT(h_entry1_q != NULL);
	configASSERT(h_entry2_q != NULL);
	configASSERT(h_exit1_q != NULL);
	configASSERT(h_exit2_q != NULL);
//    configASSERT(NULL != h_mutex_mut_sem);

    configASSERT(NULL != h_counter1_sem);
    configASSERT(NULL != h_counter2_sem);

	/* Add queue or semaphore (binary or counting) or mutex to registry. */
   	//vQueueAddToRegistry(h_entry_bin_sem, "Entry BIN Handle");
	//vQueueAddToRegistry(h_exit1_bin_sem, "Exit BIN Handle");
	//vQueueAddToRegistry(h_exit2_bin_sem, "Exit BIN Handle");
	//vQueueAddToRegistry(h_continue_bin_sem, "Continue BIN Handle");
	vQueueAddToRegistry(h_entry1_q, "Entry 1 Queue Handle");
	vQueueAddToRegistry(h_entry2_q, "Entry 2 Queue Handle");
	vQueueAddToRegistry(h_exit1_q, "Exit 1 Queue Handle");
	vQueueAddToRegistry(h_exit2_q, "Exit 2 Queue Handle");
//	vQueueAddToRegistry(h_mutex_mut_sem, "Mutex MUT Handle");

	vQueueAddToRegistry(h_counter1_sem, "counter CNT Handle");
	vQueueAddToRegistry(h_counter2_sem, "counter CNT Handle");
	/* Add threads, ... */
    BaseType_t ret;
    task_config[0].h_q = h_entry1_q;
    task_config[0].h_counter_sem = h_counter1_sem;
    /* Task A thread at priority 2 */
    ret = xTaskCreate(task_a,							/* Pointer to the function thats implement the task. */
					  "Task A Entry 1",							/* Text name for the task. This is to facilitate debugging only. */
					  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  (void*) &task_config[0],								/* We are not using the task parameter. */
					  (tskIDLE_PRIORITY + 2ul),			/* This task will run at priority 1. */
					  &h_task_a);						/* We are using a variable as task handle. */

    /* Check the thread was created successfully. */
    configASSERT(pdPASS == ret);

    task_config[1].h_q = h_entry2_q;
    task_config[1].h_counter_sem = h_counter2_sem;
    /* Task A thread at priority 2 */
    ret = xTaskCreate(task_a,							/* Pointer to the function thats implement the task. */
					  "Task AA Entry 2",							/* Text name for the task. This is to facilitate debugging only. */
					  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  (void*) &task_config[1],								/* We are not using the task parameter. */
					  (tskIDLE_PRIORITY + 2ul),			/* This task will run at priority 1. */
					  &h_task_aa);						/* We are using a variable as task handle. */

    /* Check the thread was created successfully. */
    configASSERT(pdPASS == ret);

    task_config[2].h_q = h_exit1_q;
    task_config[2].h_counter_sem = h_counter1_sem;
    /* Task B thread at priority 2 */
    ret = xTaskCreate(task_b,						/* Pointer to the function thats implement the task. */
					  "Task B Exit 1",						/* Text name for the task. This is to facilitate debugging only. */
					  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  (void*) &task_config[2],					/* We are using the task parameter. */
					  (tskIDLE_PRIORITY + 2ul),			/* This task will run at priority 1. */
					  &h_task_b);						/* We are using a variable as task handle. */

    /* Check the thread was created successfully. */
    configASSERT(pdPASS == ret);

    task_config[3].h_q = h_exit2_q;
    task_config[3].h_counter_sem = h_counter2_sem;
    /* Task B thread at priority 2 */
    ret = xTaskCreate(task_b,						/* Pointer to the function thats implement the task. */
    				  "Task BB Exit 2",						/* Text name for the task. This is to facilitate debugging only. */
    				  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  (void*) &task_config[3],					/* We are using the task parameter. */
    				  (tskIDLE_PRIORITY + 2ul),			/* This task will run at priority 1. */
    				  &h_task_bb);						/* We are using a variable as task handle. */

    /* Check the thread was created successfully. */
    //configASSERT(pdPASS == ret);

    /* Task Test thread at priority 1, periodically excites other tasks */
    ret = xTaskCreate(task_test,						/* Pointer to the function thats implement the task. */
					  "Task Test",						/* Text name for the task. This is to facilitate debugging only. */
					  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  NULL,								/* We are not using the task parameter. */
					  (tskIDLE_PRIORITY + 1ul),			/* This task will run at priority 1. */
					  &h_task_test);					/* We are using a variable as task handle. */

    /* Check the thread was created successfully. */
    configASSERT(pdPASS == ret);

    cycle_counter_init();
}

/********************** end of file ******************************************/
