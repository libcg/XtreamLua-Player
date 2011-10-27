/*
 *	XtreamLua Player - Final Version
 *	time.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#ifndef __XLP_TIME__
#define __XLP_TIME__

#include "common.h"

#include <psprtc.h>

/*
	Time.getTime(stringUnit) - Get local time.
 
		%arg string stringUnit Either "year", "month", "day", "hour", "minutes", "seconds" or "microseconds".
 
		%ret number The asked value. (year, month, day, hour, minutes, seconds or microseconds).
 */

int Time_getTime(lua_State *L);


/*
	Time.getTimeUTC(stringUnit, timeZone) - Get UTC time.
 
		%arg string stringUnit Either "year", "month", "day", "hour", "minutes", "seconds" or "microseconds".
		%arg number timeZone The time (in minutes) to add from the time of GMT +0.
 
		%ret number The asked value. (year, month, day, hour, minutes, seconds or microseconds).
 */

int Time_getTimeUTC(lua_State *L);


/*
	Time.stringTime() - Get local time and put it in a beautiful string.
 
		%arg nothing.
 
		%ret string A string like this: "Day/Month/Year - Hour:Minutes:Seconds", taken with the local time.
 */

int Time_stringTime(lua_State *L);


/*
	Time.getTick() - Get tick count.
 
		%arg nothing.
 
		%ret number The tick count.
 */

int Time_getTick(lua_State *L);


/*
	Time.getDaysInMonth(year, month) - Get the number of days in a specific month.
 
		%arg number year The year of the month.
		%arg number month The month to get the number of days.
 
		%ret number The number of days in the month.
 */

int Time_getDaysInMonth(lua_State *L);


/*
	Time.getDayOfWeek(year, month, day) - Get day of week.
 
		%arg number year The year of the day.
		%arg number The month of the day.
		%arg number The day to know.
 
		%ret string The aksed day ("Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" or "Sunday").
 */

int Time_getDayOfWeek(lua_State *L);


/*
	Time.isLeapYear(year) - Check if a year is leap or not.
 
		%arg number year The year you want to know if it is leap or not.
 
		%ret boolean true if year is leap, false if it isn't.
 */

int Time_isLeapYear(lua_State *L);


// XLP internal code //
int Time_init(lua_State *L);

static const luaL_reg Time_methods[] = { // Time methods
	{"getTime", Time_getTime},
	{"getTimeUTC", Time_getTimeUTC},
	{"stringTime", Time_stringTime},
	{"getTick", Time_getTick},
	{"getDaysInMonth", Time_getDaysInMonth},
	{"getDayOfWeek", Time_getDayOfWeek},
	{"isLeapYear", Time_isLeapYear},
	{0, 0}
};

#endif

//EOF
