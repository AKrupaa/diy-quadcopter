/*
 * runtime.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include <assert.h>
#include "runtime.h"

/* 
*	=====================================================
* 							def 
* 	=====================================================
*/
TaskHandle_t rt_tasks[rt_task_N];
QueueHandle_t rt_queues[rt_queue_N];
EventGroupHandle_t rt_evgroups[rt_evgroup_N];
TimerHandle_t rt_timers[rt_timer_N];

static void error()
{
	while (1)
		;
}

/* 
*	=====================================================
* 						free rtos init 
* 	=====================================================
*/

void rt_init()
{

	for (rt_task_t task = rt_task_0; task < rt_task_N; task++)
	{
		rt_task_def_t const *def = rt_task_def + task;
		TaskHandle_t *handle = rt_tasks + task;
		if (def->active)
		{
			if (xTaskCreate(def->pvTaskCode, def->pcName, def->usStackDepth,
							def->pvParameters, def->uxPriority, handle) != pdPASS)
			{
				error();
			}
		}
		else
		{
			*handle = 0;
		}
	}

	for (rt_queue_t queue = rt_queue_0; queue < rt_queue_N; queue++)
	{
		rt_queue_def_t const *def = rt_queue_def + queue;
		QueueHandle_t *handle = rt_queues + queue;

		if ((*handle = xQueueCreate(def->uxQueueLength, def->uxItemSize)) == 0)
		{
			error();
		}
	}

	for (rt_timer_t timer = rt_timer_0; timer < rt_timer_N; timer++)
	{
		rt_timer_def_t const *def = rt_timer_def + timer;
		TimerHandle_t *handle = rt_timers + timer;

		if ((*handle = xTimerCreate(def->pcTimerName, def->xTimerPeriodInTicks,
									def->uxAutoReload, NULL, def->pxCallbackFunction)) == 0)
		{
			error();
		}
	}

	for (rt_evgroup_t evgroup = rt_evgroup_0; evgroup < rt_evgroup_N;
		 evgroup++)
	{
		EventGroupHandle_t *handle = rt_evgroups + evgroup;

		if ((*handle = xEventGroupCreate()) == 0)
		{
			error();
		}
	}
}

/* 
*	=====================================================
* 						event group 
* 	=====================================================
*/

uint32_t rt_evbitwait_any(rt_evgroup_t event)
{
	assert(event < rt_evgroup_N);

	EventGroupHandle_t Evh = rt_evgroups[event];

	return xEventGroupWaitBits(Evh, 0x00FFFFFFu, pdTRUE, pdFALSE, portMAX_DELAY);
}

uint32_t rt_evbit_check_any(rt_evgroup_t event)
{
	assert(event < rt_evgroup_N);

	EventGroupHandle_t Evh = rt_evgroups[event];

	return xEventGroupWaitBits(Evh, 0x00FFFFFFu, pdFALSE, pdFALSE, 0);
}

uint32_t rt_evbit_clear(rt_evgroup_t event, uint32_t bit)
{
	assert(event < rt_evgroup_N);

	EventGroupHandle_t Evh = rt_evgroups[event];
	EventBits_t msk = (1u << bit);

	return xEventGroupClearBits(Evh,  // The event group being updated.
								msk); // The bits being cleared.
}

BaseType_t rt_evbit_clear_ISR(rt_evgroup_t event, uint32_t bit)
{
	assert(event < rt_evgroup_N);

	EventGroupHandle_t Evh = rt_evgroups[event];
	EventBits_t msk = (1u << bit);

	return xEventGroupClearBitsFromISR(Evh,	 // The event group being updated.
									   msk); // The bits being cleared.
}

void rt_evbit_set(rt_evgroup_t event, uint32_t bit)
{
	assert(event < rt_evgroup_N);

	EventBits_t msk = (1u << bit);
	EventGroupHandle_t Evh = rt_evgroups[event];
	xEventGroupSetBits(Evh, msk);
}

void rt_evbit_set_ISR(rt_evgroup_t event, uint32_t bit)
{
	assert(event < rt_evgroup_N);

	EventBits_t msk = (1u << bit);
	EventGroupHandle_t Evh = rt_evgroups[event];
	xEventGroupSetBitsFromISR(Evh, msk, pdFALSE);
	portYIELD_FROM_ISR(pdFALSE);
}

/* 
*	=====================================================
* 							queue 
* 	=====================================================
*/

bool rt_enqueue(rt_queue_t queue, void const *buffer)
{
	assert(queue < rt_queue_N);

	QueueHandle_t Qh = rt_queues[queue];
	TickType_t to = rt_queue_def[queue].timeout_enq;

	if (xQueueSendToBack(Qh, buffer, to) == pdPASS)
	{
		return true;
	}

	return false;
}

bool rt_enqueue_ISR(rt_queue_t queue, void const *buffer)
{
	assert(queue < rt_queue_N);

	QueueHandle_t Qh = rt_queues[queue];
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	if (xQueueSendToBackFromISR(Qh, buffer, &xHigherPriorityTaskWoken) == pdPASS)
	{
		return true;
	}

	return false;
}

bool rt_dequeue(rt_queue_t queue, void *buffer)
{
	assert(queue < rt_queue_N);

	QueueHandle_t Qh = rt_queues[queue];
	TickType_t to = rt_queue_def[queue].timeout_deq;

	if (xQueueReceive(Qh, buffer, to) == pdPASS)
	{
		return true;
	}

	return false;
}

bool rt_queue_peek(rt_queue_t queue, void *buffer)
{
	assert(queue < rt_queue_N);

	QueueHandle_t Qh = rt_queues[queue];

	if (xQueuePeek(Qh, buffer, pdMS_TO_TICKS(portMAX_DELAY)) == pdPASS)
	{
		return true;
	}

	return false;
}

/* 
*	=====================================================
* 							timer 
* 	=====================================================
*/

bool rt_timer_start(rt_timer_t timer, uint32_t timeout)
{
	assert(timer < rt_timer_N);

	return xTimerStart(rt_timers[timer], timeout);
}

bool rt_timer_start_ISR(rt_timer_t timer, BaseType_t *pxHigherPriorityTaskWoken)
{
	assert(timer < rt_timer_N);

	return xTimerStartFromISR(rt_timers[timer], pxHigherPriorityTaskWoken);
}
