#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <sys/time.h>
#include <ogc/lwp_watchdog.h>
#include "util.h"

/*
	Returns the time in miliseconds
*/
u32 GetTime(){
	return ticks_to_millisecs(gettime());
}