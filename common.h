#ifndef __XLP_COMMON__
#define __XLP_COMMON__

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

extern void luaC_collectgarbage (lua_State *L);

#include <glib2d.h>
#include <intraFont.h>
#include <libtimer.h>
#include <pspaalib.h>

/* Define */

#define setInterval(value, minVal, maxVal) \
    ((value < minVal) ? minVal : (value > maxVal) ? maxVal : value)

#define printf pspDebugScreenPrintf

#define Const(name, val) \
	lua_pushstring(L, name); \
	lua_pushnumber(L, val); \
	lua_settable(L, -3) ;

#define UserdataConvert(luaData, cData, luaType) \
	cData *get##luaData(lua_State* L, int index) { \
		cData* temp = (cData*)lua_touserdata(L, index); \
			if (temp == NULL) luaL_typerror(L, index, luaType); \
		return temp; \
	}\
	cData *push##luaData(lua_State* L) { \
		cData *pushVal = (cData*)lua_newuserdata(L, sizeof(cData)); \
		luaL_getmetatable(L, #luaData); \
		lua_pushvalue(L, -1); \
		lua_setmetatable(L, -3);\
		lua_pushstring(L, "__index"); \
		lua_pushstring(L, #luaData); \
		lua_gettable(L, LUA_GLOBALSINDEX); \
		lua_settable(L, -3); \
		lua_pop(L, 1); \
		return pushVal; \
	}\
	cData *is##luaData(lua_State* L, int index) { \
		cData *data; \
		if (lua_type(L, index) != LUA_TUSERDATA) return false; \
		data = (cData*)luaL_checkudata(L, index, #luaData);\
		if (data == NULL) return false;\
		return false; \
	}

#define UserdataRegister(NAME, METHODS, METAMETHODS) \
	luaL_newmetatable(L, NAME);  /* create new metatable for file handles */ \
	lua_pushliteral(L, "__index"); \
	lua_pushvalue(L, -2);  /* push metatable */ \
	lua_rawset(L, -3);  /* metatable.__index = metatable */ \
	\
	luaL_register(L, 0, METAMETHODS); \
	luaL_register(L, NAME, METHODS); \
	\
	lua_pushstring(L, NAME); \
	lua_gettable(L, LUA_GLOBALSINDEX); \
	luaL_getmetatable(L, NAME); \
	lua_setmetatable(L, -2); \

#define SetGlobalInt(var) \
	lua_pushinteger(L, var); \
	lua_setglobal(L, #var); \

#endif

//EOF
