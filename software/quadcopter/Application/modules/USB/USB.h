#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef enum
{
	received = 0,
	transmit,
} usb_traffic;

typedef struct
{
	usb_traffic traffic;
	size_t data_size;
	char const *data;
} xQueueUSBData;
