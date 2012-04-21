
#include <pspkernel.h>
#include <pspdebug.h>
#include <psprtc.h>

#include <libtimer.h>

Timer *createTimer()
{
	Timer* timer = (Timer*)malloc(sizeof(Timer));
	if(!timer) return NULL;
	
	memset(timer, 0, sizeof(Timer));
	
	u64 tick = 0;
	sceRtcGetCurrentTick(&tick);
	
	timer->start_time = tick;
	
	return timer;
}

void startTimer(Timer *timer)
{
	u64 tick = 0;
	sceRtcGetCurrentTick(&tick);
	
	timer->start_time = tick;
	timer->current_time = 0;
	timer->running = true;
}

void pauseTimer(Timer *timer)
{
	u64 tick = 0;
	sceRtcGetCurrentTick(&tick);
	
	if(timer->running)
		timer->pause_start = tick;
	else
	{
		timer->pause_end = tick;
		timer->pause_time = timer->pause_end - timer->pause_start;
		timer->start_time += timer->pause_time;
	}
	
	timer->running = !timer->running;
}

void updateTimer(Timer *timer)
{	
	if(!timer->running) return;
	
	u64 tick = 0;
	sceRtcGetCurrentTick(&tick);
	
	timer->current_time = tick;
	
	timer->elapsed = timer->current_time - timer->start_time;
}

void stopTimer(Timer *timer)
{
	timer->running = false;
}

void resetTimer(Timer *timer)
{	
	//memset(timer, 0, sizeof(Timer));
	
	timer->elapsed = 0;
	
	timer->running = false;
}

void freeTimer(Timer *timer)
{
	free(timer);
}

//EOF
