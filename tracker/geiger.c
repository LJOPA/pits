#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <wiringPi.h>
#include <gertboard.h>

#include "gps.h"
#include "adc.h"
#include "misc.h"

#define geigerPin 12

int count = 0;
int cps;

void incCounter() {
	if (count < uint32_max)
		count++;
}

void processData() {
	cps = count;
	count = 0;
}

void *GeigerLoop(void *some_void_ptr)
{
	// Open connections to geiger counter
	wiringPiISR(geigerPin, INT_EDGE_RISING, incCounter);
	
	// Open geiger log file for writing to
	
	
	while (1)
	{
		processData();
		GPS->cps = cps;
		
		sleep(1);
	}

	return 0;
}
