/*
 * device_init.c
 *
 *  Created on: Mar 27, 2021
 *      Author: Arkadiusz
 */

#include "device_init.h"
#include "stdint.h"

static void error(void)
{
	while (1)
		;
}

void device_init(void)
{

	uint16_t successCnt = 0;
	uint16_t modsToInit = 0;

	for (uint16_t i = 0; i < mod_N; i++)
	{
		if (modules_cfg[i].active == true)
		{
			if (modules_cfg[i].init_function() == true)
			{
				successCnt++;
			}
		}

		modsToInit++;
	}

	if (modsToInit != successCnt)
	{
		error();
	}
}
