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
#include "board.h"
//#include "task_entry_b.h"
//#include "task_exit_b.h"
//#include "task_entry_a.h"
//#include "task_exit_a.h"
#include "task_x_entry.h"
#include "task_x_exit.h"
#include "task_test.h"
#include "monitor.h"

/********************** macros and definitions *******************************/
#define G_TASKS_QUEUE_SIZE 2
#define G_TASKS_QTY_MAX 3
/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_sys	= " RTOS - Event-Triggered Systems (ETS)\r\n";
const char *p_app	= " freertos_app_example_003: Vehicular crossing\r\n";

/********************** external data declaration *****************************/
/* Declare a variable of type QueueHandle_t. This is used to reference queues*/
/* This is used to send messages from the Button task to the Led task. */
QueueHandle_t h_entry_a_q;
QueueHandle_t h_entry_b_q;
QueueHandle_t h_struct_q;
/* Declare a variable of type SemaphoreHandle_t (binary or counting) or mutex.
 * This is used to reference the semaphore that is used to synchronize a thread
 * with other thread or to ensure mutual exclusive access to...*/
SemaphoreHandle_t h_exit_a_bin_sem;
SemaphoreHandle_t h_exit_b_bin_sem;
SemaphoreHandle_t h_quantity_a_cnt_sem;
SemaphoreHandle_t h_mutex_mut_sem;
/* Declare a variable of type TaskHandle_t. This is used to reference threads. */
TaskHandle_t h_task_entry_a;
TaskHandle_t h_task_exit_a;
TaskHandle_t h_task_entry_b;
TaskHandle_t h_task_exit_b;
TaskHandle_t h_task_test;
TaskHandle_t h_monitor;

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
	h_entry_a_q = xQueueCreate( G_TASKS_QUEUE_SIZE, sizeof("AB123YZ"));
	h_exit_a_bin_sem  = xSemaphoreCreateBinary();
	h_entry_b_q = xQueueCreate( G_TASKS_QUEUE_SIZE, sizeof("AB123YZ"));
	h_exit_b_bin_sem  = xSemaphoreCreateBinary();
	h_quantity_a_cnt_sem = xSemaphoreCreateCounting(G_TASKS_QTY_MAX, G_TASKS_QTY_MAX);
	h_struct_q = xQueueCreate( G_TASKS_QUEUE_SIZE, sizeof(struct_q));
	h_mutex_mut_sem = xSemaphoreCreateMutex();
    /* Check the queue or semaphore (binary or counting) or mutex was created 
     * successfully. */
	configASSERT(h_entry_a_q != NULL);
	configASSERT(h_exit_a_bin_sem != NULL);
	configASSERT(h_entry_b_q != NULL);
	configASSERT(h_exit_b_bin_sem != NULL);
	configASSERT(h_quantity_a_cnt_sem != NULL);
	configASSERT(h_struct_q != NULL);
	configASSERT(h_mutex_mut_sem != NULL);
	/* Add queue or semaphore (binary or counting) or mutex to registry. */
	vQueueAddToRegistry(h_entry_a_q, "Entry A Queue Handle");
	vQueueAddToRegistry(h_exit_a_bin_sem,  "Exit A Semaphore Handle");
	vQueueAddToRegistry(h_entry_b_q, "Entry B Queue Handle");
	vQueueAddToRegistry(h_exit_b_bin_sem,  "Exit B Semaphore Handle");
	vQueueAddToRegistry(h_quantity_a_cnt_sem, "Quantity A Semaphore Handle");
	vQueueAddToRegistry(h_struct_q, "Struct Queue Handle");
	vQueueAddToRegistry(h_mutex_mut_sem, "Mutex Semaphore Handle");
	/* Add threads, ... */
    BaseType_t ret;

    /* Task A thread at priority 2 */
    ret = xTaskCreate(task_x_entry,						/* Pointer to the function thats implement the task. */
					  "Task Entry A",					/* Text name for the task. This is to facilitate debugging only. */
					  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  h_entry_a_q,								/* We are not using the task parameter. */
					  (tskIDLE_PRIORITY + 2ul),			/* This task will run at priority 1. */
					  &h_task_entry_a);					/* We are using a variable as task handle. */

    /* Check the thread was created successfully. */
    configASSERT(pdPASS == ret);

    /* Task B thread at priority 2 */
    ret = xTaskCreate(task_x_exit,						/* Pointer to the function thats implement the task. */
					  "Task Exit A",					/* Text name for the task. This is to facilitate debugging only. */
					  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  h_exit_a_bin_sem,								/* We are not using the task parameter. */
					  (tskIDLE_PRIORITY + 2ul),			/* This task will run at priority 1. */
					  &h_task_exit_a);					/* We are using a variable as task handle. */

    /* Check the thread was created successfully. */
    configASSERT(pdPASS == ret);

    /* Task B thread at priority 2 */
    ret = xTaskCreate(task_x_entry,						/* Pointer to the function thats implement the task. */
    				  "Task Entry B",					/* Text name for the task. This is to facilitate debugging only. */
					  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  h_entry_b_q,								/* We are not using the task parameter. */
					  (tskIDLE_PRIORITY + 2ul),			/* This task will run at priority 1. */
					  &h_task_entry_b);					/* We are using a variable as task handle. */

    /* Check the thread was created successfully. */
//    configASSERT(pdPASS == ret);

    /* Task B thread at priority 2 */
    ret = xTaskCreate(task_x_exit,						/* Pointer to the function thats implement the task. */
					  "Task Exit B",					/* Text name for the task. This is to facilitate debugging only. */
					  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  h_exit_b_bin_sem,								/* We are not using the task parameter. */
					  (tskIDLE_PRIORITY + 2ul),			/* This task will run at priority 1. */
					  &h_task_exit_b);					/* We are using a variable as task handle. */


    /* Task Test thread at priority 1, periodically excites other tasks */
    ret = xTaskCreate(task_test,						/* Pointer to the function thats implement the task. */
					  "Task Test",						/* Text name for the task. This is to facilitate debugging only. */
					  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
					  NULL,								/* We are not using the task parameter. */
					  (tskIDLE_PRIORITY + 1ul),			/* This task will run at priority 1. */
					  &h_task_test);					/* We are using a variable as task handle. */

    /* Check the thread was created successfully. */
    configASSERT(pdPASS == ret);

    ret = xTaskCreate(monitor,						/* Pointer to the function thats implement the task. */
    				  "Monitor",						/* Text name for the task. This is to facilitate debugging only. */
    				  (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. */
    				  NULL,								/* We are not using the task parameter. */
    				  (tskIDLE_PRIORITY + 1ul),			/* This task will run at priority 1. */
    				  &h_monitor);					/* We are using a variable as task handle. */

        /* Check the thread was created successfully. */
        configASSERT(pdPASS == ret);

    cycle_counter_init();
}

void semaphore_vial_control(bool color, TaskHandle_t task_id){}
/********************** end of file ******************************************/
