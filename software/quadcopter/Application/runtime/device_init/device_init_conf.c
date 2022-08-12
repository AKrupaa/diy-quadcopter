/*
 * device_init_conf.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include "device_init.h"
#include "USB.h"

module_t modules_cfg[] =
{
	{
		.init_function = usb_init,
		.name = "MODULE INIT EXAMPLE",
		.active = true
	},
};

