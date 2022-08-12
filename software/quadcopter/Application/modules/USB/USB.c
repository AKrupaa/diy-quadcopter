/*
 * USB.c
 *
 *  Created on: Aug 12, 2022
 *      Author: Arkadiusz
 */

#include "USB.h"

xQueueUSBData queueUsbData;

bool usb_init(void)
{
    memset(&queueUsbData, 0, sizeof(queueUsbData));
    return true;
}
