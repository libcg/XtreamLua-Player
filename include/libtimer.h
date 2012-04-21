#ifndef __TIMER__
#define __TIMER__

#include "../common.h"
#include <malloc.h>
#include <psptypes.h>

typedef struct
{
	u32 elapsed;
	
	bool running;
	
	u32 current_time;
	u32 start_time;
	u32 pause_time;
	u32 pause_start;
	u32 pause_end;
} Timer;

Timer *createTimer();

void startTimer(Timer *timer);

void pauseTimer(Timer *timer);

void updateTimer(Timer *timer);

void stopTimer(Timer *timer);

void resetTimer(Timer *timer);

void freeTimer(Timer *timer);

#endif

//EOF
