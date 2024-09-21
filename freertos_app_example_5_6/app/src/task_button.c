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
 * @file   : task_button.c
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
#include "button.h"
#include "led.h"
#include "app.h"

/********************** macros and definitions *******************************/
#define G_TASK_BTN_CNT_INI	0ul

#define BTN_TICK_CNT_MAX	250ul

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
const char *p_task_button		= "Task BUTTON - Demo Code";

const char *p_task_blinking_on	= "Blinking turn On ";
const char *p_task_blinking_off	= "Blinking turn Off";

btn_config_t btn_config[]	= {{BTN_A_PORT,	BTN_A_PIN,		\
								BTN_HOVER,	NOT_PRESSED,	\
								NULL},
					  	   	   {BTN_B_PORT,	BTN_B_PIN, 		\
								BTN_HOVER,	NOT_PRESSED,	\
								NULL},
							   {BTN_C_PORT,	BTN_C_PIN,		\
								BTN_HOVER,	NOT_PRESSED,	\
								NULL}};

/********************** external data declaration *****************************/
uint32_t g_task_btn_cnt;

/********************** external functions definition ************************/
/* Task AA, BB and CC thread */
void task_button(void *parameters)
{
	#if (TEST_X == TEST_0)

	g_task_btn_cnt = G_TASK_BTN_CNT_INI;

	/*  Declare & Initialize Task Function variables for argument, led, button and task */
	btn_config_t *p_btn_config = (btn_config_t *)parameters;

	static led_flag_t value_to_send = NOT_BLINKING;

	char *p_task_name = (char *)pcTaskGetName(NULL);

	/* Print out: Application Update */
	LOGGER_LOG("  %s is running - %s\r\n", p_task_name, p_task_button);

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
		g_task_btn_cnt++;

		/* Check HW Button State */
		p_btn_config->btn_state = HAL_GPIO_ReadPin(p_btn_config->btn_gpio_port, p_btn_config->btn_pin);
		if (BTN_PRESSED == p_btn_config->btn_state)
		{
			/* Check, Update and Print Led Flag */
			if (NOT_BLINKING == value_to_send)
			{
				value_to_send = BLINKING;

				/* Print out: Task execution */
				LOGGER_LOG("  %s - %s\r\n", p_task_name, p_task_blinking_on);
			}
			else
			{
				value_to_send = NOT_BLINKING;

				/* Print out: Task execution */
				LOGGER_LOG("  %s - %s\r\n", p_task_name, p_task_blinking_off);
			}
			xQueueSendToBack(p_btn_config->queue_handle, &value_to_send, portMAX_DELAY);
		}

		/* We want this task to execute every 250 milliseconds. */
		vTaskDelay(BTN_TICK_CNT_MAX);

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
