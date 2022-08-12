/*
 * runtime_conf.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include "runtime.h"
#include "runtime_conf.h"

void callback_example() {

}
/* 
*	=====================================================
* 						task def 
* 	=====================================================
*/
rt_task_def_t const rt_task_def[rt_task_N] = {
		{
			.pvTaskCode = sender_task_handler_example,
			.pcName = "EXAMPLE SENDER TASK",
			.pvParameters = NULL,
			.usStackDepth = 1u * configMINIMAL_STACK_SIZE,
			.uxPriority = 2u,
			.active = true
		},
		{
			.pvTaskCode = receiver_task_handler_example,
			.pcName = "EXAMPLE RECEIVER TASK",
			.pvParameters = NULL,
			.usStackDepth = 1u * configMINIMAL_STACK_SIZE,
			.uxPriority = 2u,
			.active = true
		},
};

/* 
*	=====================================================
* 						queue def 
* 	=====================================================
*/
rt_queue_def_t const rt_queue_def[rt_queue_N] = {
		{
			.uxQueueLength = 5,
			.uxItemSize = sizeof(unsigned char), /* insert here your size */
			.timeout_enq = pdMS_TO_TICKS(100u),
			.timeout_deq = portMAX_DELAY
		},
};

/* 
*	=====================================================
* 					event group def 
* 	=====================================================
*/

rt_evgroup_def_t const rt_evgroup_def[rt_evgroup_N] = {
	{
		.timeout = pdMS_TO_TICKS(20),
		.critical = false,
	},
};

/* 
*	=====================================================
* 						timer def 
* 	=====================================================
*/
rt_timer_def_t const rt_timer_def[rt_timer_N] = {
		{
			.pxCallbackFunction = callback_example,
			.pcTimerName = "CALLBACK EXAMPLE",
			.uxAutoReload = pdFALSE,
			.xTimerPeriodInTicks = pdMS_TO_TICKS(20)
		},
};
