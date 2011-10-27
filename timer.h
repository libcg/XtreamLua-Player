/*
 *	XtreamLua Player - Final Version
 *	timer.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#ifndef __XLP_TIMER__
#define __XLP_TIMER__

#include "common.h"


/*
	Timer.create() - Create a new timer.
 
		%arg nothing.
 
		%ret timer The created timer.
 */

int Timer_create(lua_State *L);


/*
	Timer.start(timer) - Start a timer, can be used like this: timer:start().
 
		%arg timer timer The timer to start.
 
		%ret nothing.
 */

int Timer_Start(lua_State *L);


/*
	Timer.pause(timer) - Pause a timer, can be used like this: timer:pause().
 
		%arg timer timer The timer to pause.
 
		%ret nothing.
 */

int Timer_Pause(lua_State *L);


/*
	Timer.getTime(timer) - Get the ellapsed time of a timer, can be used like this: timer:getTime().
 
		%arg timer timer The timer to get the ellapsed time.

		%ret number The ellapsed time of the timer, in microseconds.
 */

int Timer_getTime(lua_State *L);


/*
	Timer.stop(timer) - Stop a timer, can be used like this: timer:stop().
 
		%arg timer timer The timer to start.
 
		%ret nothing.
 */

int Timer_Stop(lua_State *L);


/*
	Timer.reset(timer) - Reset a timer, can be used like this: timer:reset().
 
		%arg timer timer The timer to reset.
 
		%ret nothing.
 */

int Timer_Reset(lua_State *L);


/*
	Timer.free(timer) - Free a timer and remove it from the RAM, can be used like this: timer:free().
 
		%arg timer timer The timer to free.
 
		%ret nothing.
 */

int Timer_free(lua_State *L);



// XLP internal code //
int Timer_init(lua_State *L);

static const luaL_reg Timer_methods[] = { // Timer methods
	{"create", Timer_create},
	{"start", Timer_Start},
	{"pause", Timer_Pause},
	{"getTime", Timer_getTime},
	{"stop", Timer_Stop},
	{"reset", Timer_Reset},
	{"free", Timer_free},
	{0,0}
};

static const luaL_reg Timer_metamethods[] = { // Timer metamethods
	{"__gc", Timer_free},
	{0,0}
};

#endif

// EOF
