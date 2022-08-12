/*
 * runtime_conf.h
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_RUNTIME_RUNTIME_CONF_H_
#define APPLICATION_RUNTIME_RUNTIME_CONF_H_
#include "FreeRTOS.h"
#include "task.h"

/// RTOS tasks.
typedef enum rt_task
{
	rt_task_0,
	rt_task_sender_example = rt_task_0,
	rt_task_receiver_example,
	rt_task_N
} rt_task_t;

/// RTOS queues.
typedef enum rt_queue
{
	rt_queue_0,
	rt_queue_sender_receiver = rt_queue_0,
	rt_queue_N
} rt_queue_t;

/// RTOS event groups.
typedef enum rt_evgroup
{
	rt_evgroup_0,
	rt_evgroup_event_example = rt_evgroup_0,
	rt_evgroup_N
} rt_evgroup_t;

/// RTOS timers.
typedef enum rt_timer
{
	rt_timer_0,
	rt_timer_example = rt_timer_0,
	rt_timer_N
} rt_timer_t;

portTASK_FUNCTION_PROTO(receiver_task_handler_example, unused);
portTASK_FUNCTION_PROTO(sender_task_handler_example, unused);

#endif /* APPLICATION_RUNTIME_RUNTIME_CONF_H_ */
