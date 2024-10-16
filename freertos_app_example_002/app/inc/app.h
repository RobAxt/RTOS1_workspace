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
 * @file   : app.h
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

#ifndef APP_INC_APP_H_
#define APP_INC_APP_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/
#define TEST_0 (0)
#define TEST_1 (1)
#define TEST_2 (2)

#define TEST_X (TEST_0)

/* Task A & B Counter */
#define		G_TASKS_CNT_MAX	3ul
#define		G_TASKS_CNT_INI	3ul

/********************** typedef **********************************************/
typedef struct {
	QueueHandle_t h_q;
	SemaphoreHandle_t h_counter_sem;
} task_config_t;

/********************** external data declaration ****************************/
/* Task A & B Counter */
//extern uint32_t	g_tasks_cnt;
extern task_config_t task_config[];

/* Declare a variable of type QueueHandle_t. This is used to reference queues*/
extern QueueHandle_t h_entry1_q;
extern QueueHandle_t h_entry2_q;
extern QueueHandle_t h_exit1_q;
extern QueueHandle_t h_exit2_q;

/* Declare a variable of type SemaphoreHandle_t (binary or counting) or mutex.
 * This is used to reference the semaphore that is used to synchronize a thread
 * with other thread or to ensure mutual exclusive access to...*/
//extern SemaphoreHandle_t h_entry_bin_sem;
//extern SemaphoreHandle_t h_exit1_bin_sem;
//extern SemaphoreHandle_t h_exit2_bin_sem;
//extern SemaphoreHandle_t h_continue_bin_sem;

//extern SemaphoreHandle_t h_mutex_mut_sem;

extern SemaphoreHandle_t h_counter1_sem;
extern SemaphoreHandle_t h_counter2_sem;

/* Declare a variable of type TaskHandle_t. This is used to reference threads. */
extern TaskHandle_t h_task_a;
extern TaskHandle_t h_task_aa;
extern TaskHandle_t h_task_b;
extern TaskHandle_t h_task_bb;
extern TaskHandle_t h_task_test;

/********************** external functions declaration ***********************/
void app_init(void);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* APP_INC_APP_H_ */

/********************** end of file ******************************************/
