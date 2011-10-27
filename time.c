/*
 *	XtreamLua Player - Final Version
 *	time.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#include "time.h"

/**
 *  Time.getTime:
 *
 *  - Get local time
 *
 *  @param: string - Either "year", "month", "day", "hour", "minutes", "seconds" or "microseconds"
 *  @return: value - year, month, day, hour, minutes, seconds or microseconds
 */

int Time_getTime(lua_State *L)
{
    int argc = lua_gettop(L);

    if (argc != 1)
		return luaL_error(L, "Time.getTime(stringUnit): takes one argument.");

    pspTime t;
    sceRtcGetCurrentClockLocalTime(&t);

    const char *argv = luaL_checkstring(L, 1);

    if (!strcmp(argv, "year"))
        lua_pushnumber(L, t.year);
    else if (!strcmp(argv, "month"))
        lua_pushnumber(L, t.month);
    else if (!strcmp(argv, "day"))
        lua_pushnumber(L, t.day);
    else if (!strcmp(argv, "hour"))
        lua_pushnumber(L, t.hour);
    else if (!strcmp(argv, "minutes"))
        lua_pushnumber(L, t.minutes);
    else if (!strcmp(argv, "seconds"))
        lua_pushnumber(L, t.seconds);
    else if (!strcmp(argv, "microseconds"))
        lua_pushnumber(L, t.microseconds);
    else
        return luaL_error(L, "Time.getTime(stringUnit): wrong argument.");

    return 1;
}

/**
 *  Time.getTimeUTC:
 *
 *  - Get UTC time
 *
 *  @param: string - Either "year", "month", "day", "hour", "minutes", "seconds" or "microseconds"
 *  @param: time_zone
 *  @return: value - year, month, day, hour, minutes, seconds or microseconds
 */

int Time_getTimeUTC(lua_State *L)
{
    int argc = lua_gettop(L);

	if (argc != 2)
		return luaL_error(L, "Time.getTimeUTC(stringUnit, timeZone): takes 2 arguments.");

    const char *argv = luaL_checkstring(L, 1);
    int time_zone = luaL_checknumber(L, 2);

    pspTime t;
    sceRtcGetCurrentClock(&t, time_zone);

    if (!strcmp(argv, "year"))
        lua_pushnumber(L, t.year);
    else if (!strcmp(argv, "month"))
        lua_pushnumber(L, t.month);
    else if (!strcmp(argv, "day"))
        lua_pushnumber(L, t.day);
    else if (!strcmp(argv, "hour"))
        lua_pushnumber(L, t.hour);
    else if (!strcmp(argv, "minutes"))
        lua_pushnumber(L, t.minutes);
    else if (!strcmp(argv, "seconds"))
        lua_pushnumber(L, t.seconds);
    else if (!strcmp(argv, "microseconds"))
        lua_pushnumber(L, t.microseconds);
    else
        return luaL_error(L, "Time.getTimeUTC(stringUnit, time_zone): wrong stringUnit argument.");

    return 1;
}

int Time_stringTime(lua_State *L)
{
    int argc = lua_gettop(L);
    if (argc != 6)
        return luaL_error(L, "Time.stringTime(): takes no argument.");

	pspTime t;
    sceRtcGetCurrentClockLocalTime(&t);
	
	int value[6] = {t.day, t.month, t.year, t.hour, t.minutes, t.seconds};
	
    int i;
    char buffer[25] = {0};
    char signe[6] = "//-::\0";

    for (i = 0; i < 6; i++)
    {
        if (i == 2)
            sprintf(buffer, "%s%i %c ", buffer, value[i], signe[i]);
        else if (value[i] < 10)
            sprintf(buffer, "%s0%i%c", buffer, value[i], signe[i]);
        else
            sprintf(buffer, "%s%i%c", buffer, value[i], signe[i]);
    }

    lua_pushstring(L, buffer);
    return 1;
}

/**
 *  Time.getTick:
 *
 *  - Get tick count
 *
 *  @param: none
 *  @return: tick count
 */

int Time_getTick(lua_State *L)
{
    int argc = lua_gettop(L);

    if (argc != 0)
        return luaL_error(L, "Time.getTick(): takes no argument.");

    u64 tick;
    sceRtcGetCurrentTick(&tick);

    lua_pushnumber(L, tick);

    return 1;
}

/**
 *  Time.getDaysInMonth:
 *
 *  - Get number of days in a specific month
 *
 *  @param: year
 *  @param: month
 *  @return: number of days in month
 */

int Time_getDaysInMonth(lua_State *L)
{
    int argc = lua_gettop(L);

    if (argc != 2)
        return luaL_error(L, "Time.getDaysInMonth(year, month): takes 2 arguments.");

    int year = luaL_checknumber(L, 1);
    int month = luaL_checknumber(L, 2);
    int nb_days = sceRtcGetDaysInMonth(year, month);

	if (nb_days < 0)
		return luaL_error(L, "Time.getDaysInMonth(year, month): Unexpected error");

	lua_pushnumber(L, nb_days);

    return 1;
}

/**
 *  Time.getDayOfWeek:
 *
 *  - Get day of week (0 - 6)
 *
 *  @param: year
 *  @param: month
 *  @param: day
 *  @return: string - Monday, Tuesday,Wednesday, Thursday, Friday, Saturday, Sunday
 */

int Time_getDayOfWeek(lua_State *L)
{
    int argc = lua_gettop(L);

    if (argc != 3)
        return luaL_error(L, "Time.getDayOfWeek(year, month, day): takes 3 arguments.");

    int year = luaL_checknumber(L, 1);
    int month = luaL_checknumber(L, 2);
    int day = luaL_checknumber(L, 3);

    int day_of_week = sceRtcGetDayOfWeek(year, month, day);

    char weekdays[7][12] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    lua_pushstring(L, weekdays[day_of_week - 1]);

    return 1;
}

/**
 *  Time.isLeapYear:
 *
 *  - Checks if year is a leap year
 *
 *  @param: year
 *  @return: 1 if year is leap year, else 0
 */

int Time_isLeapYear(lua_State *L)
{
    int argc = lua_gettop(L);

    if (argc != 1)
        return luaL_error(L, "Time.isLeapYear(year): takes one argument.");

    int year = luaL_checknumber(L, 1);

	lua_pushboolean(L, sceRtcIsLeapYear(year) ? true : false);

    return 1;
}


int Time_init(lua_State *L)
{
	luaL_openlib(L, "Time", Time_methods, 0);
	
	return 1;
}

// EOF
