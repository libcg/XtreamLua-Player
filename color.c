/*
 *	XtreamLua Player - Final Version
 *	color.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
*/

#include "color.h"

UserdataConvert(Color, g2dColor, "Color")

int Color_create(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 3 && argc != 4) return luaL_error(L, "Color.create(r,g,b [,a]): wrong number of arguments");
	
	unsigned r,g,b,a = 255;
	
	r = setInterval(luaL_checkint(L, 1), 0, 255);
	g = setInterval(luaL_checkint(L, 2), 0, 255);
	b = setInterval(luaL_checkint(L, 3), 0, 255);
	
	if (argc == 4)
		a = setInterval(luaL_checkint(L, 4), 0, 255);
	
	lua_pushnumber(L, G2D_RGBA(r,g,b,a));
	
	return 1;
}

int Color_getR(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Color.getR(color): wrong number of arguments");
	
	u32 color = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, G2D_GET_R(color));
	
	return 1;
}

int Color_getG(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Color.getG(color): wrong number of arguments");
	
	u32 color = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, G2D_GET_G(color));
	
	return 1;
}

int Color_getB(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Color.getB(color): wrong number of arguments");
	
	u32 color = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, G2D_GET_B(color));
	
	return 1;
}

int Color_getA(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Color.getA(color): wrong number of arguments");
	
	u32 color = luaL_checknumber(L, 1);
	
	lua_pushnumber(L, G2D_GET_A(color));
	
	return 1;
}

int Color_getColor(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1 && argc != 2) return luaL_error(L, "Color.getColor(color [,channel]): wrong number of arguments");
	
	u32 color = luaL_checknumber(L, 1);
	
	if (argc == 1)
	{
		lua_pushnumber(L, G2D_GET_R(color));
		lua_pushnumber(L, G2D_GET_G(color));
		lua_pushnumber(L, G2D_GET_B(color));
		lua_pushnumber(L, G2D_GET_A(color));
		
		return 4;
	}
	else
	{
		const char *str = luaL_checkstring(L, 2);
		if (!strcmp(str, "R"))
			lua_pushnumber(L, G2D_GET_R(color));
		else if (!strcmp(str, "G"))
			lua_pushnumber(L, G2D_GET_G(color));
		else if (!strcmp(str, "B"))
			lua_pushnumber(L, G2D_GET_B(color));
		else if (!strcmp(str, "A"))
			lua_pushnumber(L, G2D_GET_A(color));
		else
			return luaL_error(L, "Color.getColor(color, string): string input must be: R, G, B or A.");
	}
	
	return 1;
}

/*int Color_tostring(lua_State *L)
{
	gColor color = getColor(L, 1);
	lua_pushfstring(L, "Color: R=%d, G=%d, B=%d, A=%d", G_GET_R(color), G_GET_G(color), G_GET_B(color), G_GET_A(color));
	
	return 1;
}*/

int Color_init(lua_State *L)
{
	luaL_register(L, "Color", Color_methods);
	
	return 1;
}

//EOF
