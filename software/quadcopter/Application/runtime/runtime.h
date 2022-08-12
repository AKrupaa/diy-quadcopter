/*
 * runtime.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include <stdbool.h>
#include <stdint.h>

#include "runtime_conf.h"

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"

typedef struct rt_task_definition
{
	TaskFunction_t pvTaskCode;
	const char *pcName;
	void *pvParameters;
	UBaseType_t uxPriority;
	uint16_t usStackDepth;
	//	TaskHandle_t *pxCreatedTask;
	bool active;
} rt_task_def_t;

typedef struct rt_queue_definition
{
	UBaseType_t uxQueueLength;
	UBaseType_t uxItemSize;
	TickType_t timeout_enq;
	TickType_t timeout_deq;
} rt_queue_def_t;

typedef struct rt_evgroup_def
{
	TickType_t timeout;
	bool critical;
} rt_evgroup_def_t;

typedef struct rt_timer_definition
{
	char const *pcTimerName;
	uint32_t xTimerPeriodInTicks;
	UBaseType_t uxAutoReload;
	TimerCallbackFunction_t pxCallbackFunction;
} rt_timer_def_t;

/***********************************************/
/* check runtime_conf.c */
extern const rt_task_def_t rt_task_def[rt_task_N];
extern const rt_queue_def_t rt_queue_def[rt_queue_N];
extern const rt_timer_def_t rt_timer_def[rt_timer_N];
extern const rt_evgroup_def_t g_rt_evgroups_def[rt_evgroup_N];

/* check runtime.c */
extern TaskHandle_t rt_tasks[rt_task_N];
extern QueueHandle_t rt_queues[rt_queue_N];
extern EventGroupHandle_t rt_evgroups[rt_evgroup_N];
extern TimerHandle_t rt_timers[rt_timer_N];
/*
 *	=====================================================
 * 						free rtos init
 * 	=====================================================
 */
void rt_init(void);
/*
 *	=====================================================
 * 						event group
 * 	=====================================================
 */
size_t rt_evbitwait_any(rt_evgroup_t event);
size_t rt_evbit_check_any(rt_evgroup_t event);
size_t rt_evbit_clear(rt_evgroup_t event, uint32_t bits_to_clear);
BaseType_t rt_evbit_clear_ISR(rt_evgroup_t event, uint32_t bits_to_clear);
void rt_evbit_set(rt_evgroup_t event, uint32_t bit);
void rt_evbit_set_ISR(rt_evgroup_t event, uint32_t bit);
/*
 *	=====================================================
 * 							queue
 * 	=====================================================
 */
bool rt_enqueue(rt_queue_t queue, void const *buffer);
bool rt_enqueue_ISR(rt_queue_t queue, void const *buffer);
bool rt_dequeue(rt_queue_t queue, void *buffer);
bool rt_queue_peek(rt_queue_t queue, void *buffer);
/*
 *	=====================================================
 * 							timer
 * 	=====================================================
 */
bool rt_timer_start(rt_timer_t timer, uint32_t timeout);
bool rt_timer_start_ISR(rt_timer_t timer, BaseType_t *pxHigherPriorityTaskWoken);
