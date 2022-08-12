/*
 * device_init.h
 *
 *  Created on: Mar 27, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_RUNTIME_DEVICE_INIT_H_
#define APPLICATION_RUNTIME_DEVICE_INIT_H_

#include "stdbool.h"

void device_init(void);

typedef struct
{
	bool (*init_function)(void);
	char const *name;
	bool active;
} module_t;

typedef enum
{
	mod_0,
	mod_USB = mod_0,
	mod_N
} moduleName_t;

extern module_t modules_cfg[];

#endif /* APPLICATION_RUNTIME_DEVICE_INIT_H_ */
