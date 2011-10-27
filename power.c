/*
 *	XtreamLua Player - Final Version
 *	power.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#include "power.h"

#include <psppower.h>

/**
 *  Power.isPowerOnline:
 *
 *  - Checks if unit is plugged in
 *
 *  @param: none
 *  @return: 1 if plugged in, else 0
 */

int Power_isPowerOnline(lua_State *L)
{
	
	lua_pushboolean(L, scePowerIsPowerOnline() ? true : false);

    return 1;
}

/**
 *  Power.isBatteryExist:
 *
 *  - Checks if battery is present
 *
 *  @param: none
 *  @return: 1 if battery is present, else 0
 */

int Power_isBatteryExist(lua_State *L)
{
    lua_pushboolean(L, scePowerIsBatteryExist() ? true : false);

    return 1;
}

/**
 *  Power.isBatteryCharging:
 *
 *  - Checks if battery is charging
 *
 *  @param: none
 *  @return: 1 if battery is charging, else 0
 */

int Power_isBatteryCharging(lua_State *L)
{
	lua_pushboolean(L, scePowerIsBatteryCharging() ? true : false);

    return 1;
}

/**
 *  Power.isLowBattery:
 *
 *  - Checks if voltage battery is low
 *
 *  @param: none
 *  @return: 1 if battery voltage is low, else 0
 */

int Power_isLowBattery(lua_State *L)
{
	lua_pushboolean(L, scePowerIsLowBattery() ? true : false);

    return 1;
}

/**
 *  Power.getBatteryLifePercent:
 *
 *  - Get battery life in percent
 *
 *  @param: none
 *  @return: battery percentage (0 - 100)
 */

int Power_getBatteryLifePercent(lua_State *L)
{
    lua_pushnumber(L, scePowerGetBatteryLifePercent());

    return 1;
}

/**
 *  Power.getBatteryLifeTime:
 *
 *  - Get battery life as time
 *
 *  @param: none
 *  @return: battery life in minutes
 */

int Power_getBatteryLifeTime(lua_State *L)
{
    lua_pushnumber(L, scePowerGetBatteryLifeTime());

    return 1;
}

/**
 *  Power.getBatteryTemp:
 *
 *  - Get battery temperature in °C
 *
 *  @param: none
 *  @return: battery temperature in °C
 */

int Power_getBatteryTemp(lua_State *L)
{
    lua_pushnumber(L, scePowerGetBatteryTemp());

    return 1;
}

/**
 *  Power.getBatteryVolt:
 *
 *  - Get battery voltage
 *
 *  @param: none
 *  @return: string - battery voltage
 */

int Power_getBatteryVolt(lua_State *L)
{
    int volt = scePowerGetBatteryVolt();
    char c_volt[6] = {0};
    sprintf(c_volt, "%#0.3lf", volt/1000.0);
    lua_pushstring(L, c_volt);

    return 1;
}

/**
 *  Power.setCpuFrequency:
 *
 *  - Set cpu frequency
 *
 *  @param: cpu frequency (1 - 333 MHz)
 */

int Power_setCpuFrequency(lua_State *L)
{
    int argc = lua_gettop(L);

    if (argc < 1)
        return luaL_error(L, "Error : Too few arguments to function setCpuFrequency(cpufreq)");
    else if (argc > 1)
        return luaL_error(L, "Error : Too many arguments to function setCpuFrequency(cpufreq)");

    int cpu = luaL_checknumber(L, 1);

    if (cpu < 1 || cpu > 333)
        return luaL_error(L, "Error : Argument is < 1 or > 333");

    scePowerSetCpuClockFrequency(cpu);

    return 0;
}

/**
 *  Power.setBusFrequency:
 *
 *  - Set bus frequency
 *
 *  @param: bus frequency (1 - 167 MHz)
 */

int Power_setBusFrequency(lua_State *L)
{
    int argc = lua_gettop(L);

    if (argc < 1)
        return luaL_error(L, "Error : Too few arguments to function setBusFrequency(busfreq)");
    else if (argc > 1)
        return luaL_error(L, "Error : Too many arguments to function setBusFrequency(busfreq)");

    int bus = luaL_checknumber(L, 1);

    if (bus < 1 || bus > 167)
        return luaL_error(L, "Error : Argument is < 1 or > 167");

    scePowerSetBusClockFrequency(bus);

    return 0;
}

/**
 *  Power.getCpuFrequency:
 *
 *  - Get cpu frequency
 *
 *  @param: none
 *  @return: cpu frequency (1 - 333 MHz)
 */

int Power_getCpuFrequency(lua_State *L)
{
    lua_pushnumber(L, scePowerGetCpuClockFrequency());

    return 1;
}

/**
 *  Power.getBusFrequency:
 *
 *  - Get bus frequency
 *
 *  @param: none
 *  @return: bus frequency (1 - 167 MHz)
 */

int Power_getBusFrequency(lua_State *L)
{
    lua_pushnumber(L, scePowerGetBusClockFrequency());

    return 1;
}

/**
 *  Power.setClockFrequency:
 *
 *  - Set cpu frequency
 *
 *  @param: pll frequency (1 - 333 MHz)
 *  @param: cpu frequency (1 - 333 MHz)
 *  @param: bus frequency (1 - 167 MHz)
 *
 *  and:
 *      cpufreq <= pllfreq
 *      busfreq*2 <= pllfreq
 */

int Power_setClockFrequency(lua_State *L)
{
    int argc = lua_gettop(L);

    if (argc < 3)
        return luaL_error(L, "Error : Too few arguments to function setClockFrequency(pllfreq, cpufreq, busfreq)");
    else if (argc > 3)
        return luaL_error(L, "Error : Too many arguments to function setClockFrequency(pllfreq, cpufreq, busfreq)");

    int pllfreq = luaL_checknumber(L, 1);
    int cpufreq = luaL_checknumber(L, 2);
    int busfreq = luaL_checknumber(L, 3);

    if (pllfreq < 1 || pllfreq > 333)
        return luaL_error(L, "Error : pllfreq < 1 or pllfreq > 333");
    if (cpufreq < 1 || cpufreq > 333)
        return luaL_error(L, "Error : cpufreq < 1 or cpufreq > 333");
    if (busfreq < 1 || busfreq > 167)
        return luaL_error(L, "Error : busfreq < 1 or busfreq > 167");

    if (cpufreq <= pllfreq)
        if(busfreq*2 <= pllfreq)
            scePowerSetClockFrequency(pllfreq, cpufreq, busfreq);
        else
            return luaL_error(L, "Error : busfreq * 2 > pllfreq");
    else
        return luaL_error(L, "Error : cpufreq > pllfreq");

    return 0;
}

/**
 *  Power.lockPowerSwitch:
 *
 *  - Lock power switch
 *
 *  Note: if the power switch is toggled while locked
 *  it will fire immediately after being unlocked.
 *
 *  @param: none
 */

int Power_lockPowerSwitch(lua_State *L)
{
    scePowerLock(0);

    return 0;
}

/**
 *  Power.unlockPowerSwitch:
 *
 *  - Unlock power switch
 *
 *  @param: none
 */

int Power_unlockPowerSwitch(lua_State *L)
{
    scePowerUnlock(0);

    return 0;
}

/**
 *  Power.tick:
 *
 *  - Generate a power tick, preventing unit from
 *    powering off and turning off display.
 *
 *  @param: type : 0 (PSP_POWER_TICK_ALL), 1 (PSP_POWER_TICK_SUSPEND) or 2 (PSP_POWER_TICK_DISPLAY)
 */

int Power_tick(lua_State *L)
{
    int argc = lua_gettop(L);

	if (argc != 1)
        return luaL_error(L, "Power.tick(tickMode): takes one argument, either POWER_TICK_ALL, POWER_TICK_SUSPEND or POWER_TICK_DISPLAY.");

    int type = luaL_checknumber(L, 1);

    switch (type)
    {
        case POWER_TICK_ALL:
            scePowerTick(PSP_POWER_TICK_ALL);
            break;
        case POWER_TICK_SUSPEND:
            scePowerTick(PSP_POWER_TICK_SUSPEND);
            break;
        case POWER_TICK_DISPLAY:
            scePowerTick(PSP_POWER_TICK_DISPLAY);
            break;
        default:
            return luaL_error(L, "Power.tick(tickMode): Wrong type");
    }

    return 0;
}

/**
 *  Power.standby:
 *
 *  - Request the PSP to go into standby
 *
 *  @param: none
 */

int Power_standby(lua_State *L)
{
    scePowerRequestStandby();

    return 0;
}

/**
 *  Power.suspend:
 *
 *  - Request the PSP to go into suspend
 *
 *  @param: none
 */

int Power_suspend(lua_State *L)
{
    scePowerRequestSuspend();

    return 0;
}


int Power_init(lua_State *L)
{
	SetGlobalInt(POWER_TICK_ALL)
	SetGlobalInt(POWER_TICK_SUSPEND)
	SetGlobalInt(POWER_TICK_DISPLAY)
	
	luaL_openlib(L, "Power", Power_methods, 0);
	
	return 1;
}

