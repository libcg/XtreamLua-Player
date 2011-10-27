/*
 *	XtreamLua Player - Final Version
 *	ctrl.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#include "ctrl.h"

UserdataConvert(Ctrl, SceCtrlData, "Ctrl data") // Define Controls conversion

//Set a button, then it will be able to be used in lua code
#define setButton(name, enum) \
	int Ctrl_##name(lua_State *L) \
	{ \
		if (lua_gettop(L) != 1) return luaL_error(L, "Argument error, function must be called with no arguments and with a colon; e.g: pad:cross()."); \
		SceCtrlData *pad = getCtrl(L, 1); \
		lua_pushboolean(L, (pad->Buttons &enum) ? true : false); \
		return 1; \
	}

//Each button of the PSP
setButton(cross, PSP_CTRL_CROSS); 
setButton(circle, PSP_CTRL_CIRCLE);
setButton(square, PSP_CTRL_SQUARE);
setButton(triangle, PSP_CTRL_TRIANGLE);

setButton(down, PSP_CTRL_DOWN);
setButton(right, PSP_CTRL_RIGHT);
setButton(left, PSP_CTRL_LEFT);
setButton(up, PSP_CTRL_UP);

setButton(l, PSP_CTRL_LTRIGGER);
setButton(r, PSP_CTRL_RTRIGGER);

setButton(start, PSP_CTRL_START);
setButton(select, PSP_CTRL_SELECT);
setButton(note, PSP_CTRL_NOTE);
setButton(home, PSP_CTRL_HOME);

setButton(hold, PSP_CTRL_HOME);

int Ctrl_read(lua_State *L)
{
	SceCtrlData *pad = pushCtrl(L);
	
	sceCtrlPeekBufferPositive(pad, 1);
	
	return 1;
}

int Ctrl_buttons(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "Argument error, function must be called with no arguments and with a colon; e.g: pad:buttons().");
	
	SceCtrlData *pad = getCtrl(L, 1);
	
	lua_pushnumber(L, pad->Buttons);
	
	return 1;
}


int Ctrl_analogX(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "Argument error, function must be called with no arguments and with a colon; e.g: pad:Lx().");
	
	SceCtrlData *pad = getCtrl(L, 1);
	
	lua_pushnumber(L, pad->Lx - 128);
	
	return 1;
}

int Ctrl_analogY(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "Argument error, function must be called with no arguments and with a colon; e.g: pad:Ly().");
	
	SceCtrlData *pad = getCtrl(L, 1);
	
	lua_pushnumber(L, pad->Ly - 128);
	
	return 1;
}


int Ctrl_tostring(lua_State *L)
{
	lua_pushfstring(L, "Ctrl: %d", getCtrl(L, 1)->Buttons);
	return 1;
}

int Ctrl_equal(lua_State *L) 
{
	SceCtrlData *c = getCtrl(L, 1);
	SceCtrlData *d = getCtrl(L, 2);
	
	lua_pushboolean(L, c->Buttons == d->Buttons ? true : false );
	return 1;
}

int Ctrl_init(lua_State *L)
{
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	UserdataRegister("Ctrl", Ctrl_methods, Ctrl_metamethods)

	return 1;
}


//EOF
