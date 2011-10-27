/*
 *	XtreamLua Player - Final Version
 *	timer.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#include "timer.h"

UserdataConvert(Timer, Timer*, "Timer")

int Timer_create(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 0) return luaL_error(L, "Timer.create(): takes no argument.");
	
	Timer* timer = createTimer();
	if(!timer)return luaL_error(L, "Timer.create: error creating timer.");;
	
	Timer **luaTimer;
	luaTimer = pushTimer(L);
	*luaTimer = timer;
	
	return 1;
}

int Timer_Start(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "timer:start(): takes zero argument and must be called with a colon.");
	
	Timer *timer = *getTimer(L, 1);
	
	startTimer(timer);
	
	return 0;
}

int Timer_Pause(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "timer:pause(): takes zero argument and must be called with a colon.");
	
	Timer *timer = *getTimer(L, 1);
	
	pauseTimer(timer);
	
	return 0;
}

int Timer_getTime(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "timer:getTime(): takes zero argument and must be called with a colon.");
	
	Timer *timer = *getTimer(L, 1);
	
	if (timer->running)
		updateTimer(timer);
	
	lua_pushnumber(L, timer->elapsed);
	
	return 0;
}

int Timer_Stop(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "timer:stop(): takes zero argument and must be called with a colon.");
	
	Timer *timer = *getTimer(L, 1);
	
	stopTimer(timer);
	
	return 0;
}

int Timer_Reset(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "timer:reset(): takes zero argument and must be called with a colon.");
	
	Timer *timer = *getTimer(L, 1);
	
	resetTimer(timer);
	
	return 0;
}

int Timer_free(lua_State *L)
{
	freeTimer(*getTimer(L, 1));
	
	return 0;
}

int Timer_init(lua_State *L)
{
	UserdataRegister("Timer", Timer_methods, Timer_metamethods)
	
	return 1;
}

