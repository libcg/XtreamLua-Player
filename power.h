/*
 *	XtreamLua Player - Final Version
 *	power.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#ifndef __XLP_POWER__
#define __XLP_POWER__

#include "common.h"

enum POWER_TICK {
	POWER_TICK_ALL, POWER_TICK_SUSPEND, POWER_TICK_DISPLAY
};


/*
	Power.isPowerOnline() - Check if unit is plugged in.
 
		%arg nothing.
 
		%ret boolean true if it is plugged in, false if it isn't.
 */

int Power_isPowerOnline(lua_State *L);


/*
	Power.isBatteryExist() - Check if battery is present.
 
		%arg nothing.
 
		%ret boolean true if it is present, false if it isn't.
 */

int Power_isBatteryExist(lua_State *L);


/*
	Power.isBatteryCharging() - Check if battery is charging.
 
		%arg nothing.
 
		%ret boolean true if it is charging, false if it isn't.
 */

int Power_isBatteryCharging(lua_State *L);


/*
	Power.isLowBattery() - Check if voltage battery is low.
 
		%arg nothing.
 
		%ret boolean true if it is low, false if it isn't.
 */

int Power_isLowBattery(lua_State *L);


/*
	Power.getBatteryLifePercent() - Get the battery life in percent.
 
		%arg nothing.
 
		%ret number The battery percentage, between 0 -> 100.
 */

int Power_getBatteryLifePercent(lua_State *L);


/*
	Power.getBatteryLifeTime() - Get the battery life as time.
 
		%arg nothing.
 
		%ret number The battery life time, in minutes.
 */

int Power_getBatteryLifeTime(lua_State *L);


/*
	Power.getBatteryTemp() - Get the battery temperature, in °C.
 
		%arg nothing.
 
		%ret number The battery temperature, in °C.
 */

int Power_getBatteryTemp(lua_State *L);


/*
	Power.getBatteryVolt() - Get battery voltage.
 
		%arg nothing.
 
		%ret string The battery voltage as a string.
 */

int Power_getBatteryVolt(lua_State *L);


/*
	Power.setCpuFrequency(cpu) - Set the cpu frequency.
 
		%arg number cpu The new cpu value, between 1 -> 333 MHz.
 
		%ret nothing.
 */

int Power_setCpuFrequency(lua_State *L);


/*
	Power.setBusFrequency(bus) - Set the bus frequency.
 
		%arg number bus The new bus value, between 1 -> 167 MHz.
 
		%ret nothing.
 */

int Power_setBusFrequency(lua_State *L);


/*
	Power.getCpuFrequency() - Get the cpu frequency.
 
		%arg nothing.
 
		%ret number The cpu frequency, between 1 -> 333 MHz.
 */

int Power_getCpuFrequency(lua_State *L);


/*
	Power.getBusFrequency() - Get the bus frequency.
 
		%arg nothing.

		%ret number The bus frequency, between 1 -> 167 MHz.
 */

int Power_getBusFrequency(lua_State *L);


/*
	Power.setClockFrequency(pllfreq, cpufreq, busfreq) - Set the clock frequency.
 
		%arg number pllfreq The pll frequency, between 1 -> 333 MHz.
		%arg number cpufreq The cpu frequency, between 1 -> pllfreq MHz.
		%arg number busfreq The bus frequency, between 1 -> pllfreq/2 MHz.
 
		%ret nothing.
 */

int Power_setClockFrequency(lua_State *L);


/*
	Power.lockPowerSwitch() - Lock power switch. Note: if the power switch is toggled while locked, it will fire immediately after being unlocked.
 
		%arg nothing.

		%ret nothing.
 */

int Power_lockPowerSwitch(lua_State *L);


/*
	Power.unlockPowerSwitch() - Unlock power switch.
 
		%arg nothing.
 
		%ret nothing.
 */

int Power_unlockPowerSwitch(lua_State *L);


/*
	Power.tick(tickMode) - Generate a power tick, preventing unit from powering off and/or turning off display.
 
		%arg mode tickMode Either PSP_POWER_TICK_ALL, PSP_POWER_TICK_SUSPEND or PSP_POWER_TICK_DISPLAY.
 
		%ret nothing.
 */

int Power_tick(lua_State *L);


/*
	Power.standby() - Request the PSP to go into standby.
 
		%arg nothing.
 
		%ret nothing.
 */

int Power_standby(lua_State *L);


/*
	Power.suspend() - Request the PSP to go into suspend.
 
		%arg nothing.
 
		%ret nothing.
 */

int Power_suspend(lua_State *L);



// XLP internal code //
int Power_init(lua_State *L);

static const luaL_reg Power_methods[] = { // Power methods
    {"isPowerOnline", Power_isPowerOnline},
    {"isBatteryExist", Power_isBatteryExist},
    {"isBatteryCharging", Power_isBatteryCharging},
    {"isLowBattery", Power_isLowBattery},
    {"getBatteryLifePercent", Power_getBatteryLifePercent},
    {"getBatteryLifeTime", Power_getBatteryLifeTime},
    {"getBatteryTemp", Power_getBatteryTemp},
    {"getBatteryVolt", Power_getBatteryVolt},
    {"setCpuFrequency", Power_setCpuFrequency},
    {"setBusFrequency", Power_setBusFrequency},
    {"getCpuFrequency", Power_getCpuFrequency},
    {"getBusFrequency", Power_getBusFrequency},
	{"setClockFrequency", Power_setClockFrequency},
    {"lockPowerSwitch", Power_lockPowerSwitch},
    {"unlockPowerSwitch", Power_unlockPowerSwitch},
    {"tick", Power_tick},
    {"standby", Power_standby},
    {"suspend", Power_suspend},
    {0, 0}
};
#endif

//EOF

