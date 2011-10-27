/*
 *	XtreamLua Player - Final Version
 *	intra.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#include "intra.h"

#include <pspgu.h>

UserdataConvert(intraFont, intraFont*, "Font")

#define intraFont_Const(name, val)\
	lua_pushstring(L, name);\
	lua_pushnumber(L, val);\
	lua_settable(L, -3);

int intraFont_load(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "intraFont.load(fontpath): must be called with only one argument");
	lua_gc(L, LUA_GCCOLLECT, 0);
		intraFont *font = intraFontLoad(luaL_checkstring(L, 1), INTRAFONT_CACHE_ASCII);
	
	if (font == NULL) return luaL_error(L, "intraFont.load: error loading font.");
	
	intraFont **luaFont;
	luaFont = pushintraFont(L);	
	*luaFont = font;	
	
	return 1;
}

int intraFont_print(lua_State *L) //intraFont.print(x,y, font, text, size, color, shadowColor, angle, centered)
{
	int argc = lua_gettop(L);
	if (argc < 4 || argc > 9) return luaL_error(L, "font:print(x, y, text [,size, color, shadowColor, angle, alignMode]) must be called with 3, 4, 5, 6, 7 or 8 arguments and must be called with a colon.");
	
	intraFont *font = *getintraFont(L, 1);
	if (font == NULL) return luaL_error(L, "intraFont.print: font error has occured");
	
	const char *text = luaL_checkstring(L, 4);
	
	float size = (argc >= 5) ? luaL_checknumber(L, 5) : 1.f;
	
	g2dColor color = (argc >= 6) ? luaL_checknumber(L, 6) : 0xFFFFFFFF;
	g2dColor shadowColor = (argc >= 7) ? luaL_checknumber(L, 7) : 0;
	
	float angle = (argc >= 8) ? luaL_checknumber(L, 8) : 0.f;
	
	int mode = (argc == 9) ? luaL_checknumber(L, 9) : 0; 
	
	intraFontSetStyle(font, size, color, shadowColor, angle, mode);
	
	lua_pushnumber(L, intraFontPrint(font, luaL_checknumber(L, 2), luaL_checknumber(L, 3), text));
	
	return 1;
}


//Functions by JiiCeii:
int intraFont_PrintBordered(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 4 || argc > 9) return luaL_error(L, "font:printBordered(x,y, text [,size, color, borderColor, angle, alignMode]) must be called with 3, 4, 5, 6, 7 or 8 arguments and must be called with a colon.");
	
	int x = luaL_checkint(L, 2) , y = luaL_checkint(L, 3);
	
	intraFont *font = *getintraFont(L, 1);
	if (font == NULL) return luaL_error(L, "intraFont.printBordered: Error setting font.");
	
	const char *text = luaL_checkstring(L, 4);
	
	float size = (argc >= 5) ? luaL_checknumber(L, 5) : 1.f;
	
	g2dColor color = (argc >= 6) ? luaL_checknumber(L, 6) : 0xFFFFFFFF;
	g2dColor borderColor = (argc >= 7) ? luaL_checknumber(L, 7) : 0xFF000000;
	
	float angle = (argc >= 8) ? luaL_checknumber(L, 8) : 0.f;
	
	int mode = (argc == 9) ? luaL_checknumber(L, 9) : 0; 
	
	
	lua_pushnumber(L, ContouredText(x, y, font, text, size, angle, color, borderColor, mode));
	
	return 1;
}

int intraFont_PrintUnderlined(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 4 || argc > 8) return luaL_error(L, "font:printUnderlined(x,y, text [,size, color, lineColor, alignMode]) must be called with 3, 4, 5, 6 or 7 arguments and must be called with a colon.");
	
	int x = luaL_checkint(L, 2) , y = luaL_checkint(L, 3);
	
	intraFont *font = *getintraFont(L, 1);
	if (font == NULL) return luaL_error(L, "intrafont.printUnderlined: Error setting font.");
	
	const char *text = luaL_checkstring(L, 4);
	
	float size = (argc >= 5) ? luaL_checknumber(L, 5) : 1.f;
	
	g2dColor color = (argc >= 6) ? luaL_checknumber(L, 6) : 0xFFFFFFFF;
	g2dColor lineColor = (argc >= 7) ? luaL_checknumber(L, 7) : 0xFF000000;
	
	int mode = (argc == 8) ? luaL_checknumber(L, 8) : 0;
	
	lua_pushnumber(L, UnderLinedText(x, y, font, text, size, 0, color, lineColor, mode));
	
	return 1;
}

int intraFont_PrintReversed(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 4 || argc > 9) return luaL_error(L, "font:printReversed(x,y, text [,size, color, shadowColor, angle, alignMode]) must be called with 3, 4, 5, 6, 7 or 8 arguments and must be called with a colon.");
	
	int x = luaL_checkint(L, 2) , y = luaL_checkint(L, 3);
	
	intraFont *font = *getintraFont(L, 1);
	if (font == NULL) return luaL_error(L, "intrafont.printReversed: Error setting font.");
	
	const char *text = luaL_checkstring(L, 4);
	
	float size = (argc >= 5) ? luaL_checknumber(L, 5) : 1.f;
	
	g2dColor color = (argc >= 6) ? luaL_checknumber(L, 6) : 0xFFFFFFFF;
	g2dColor shadowColor = (argc >= 7) ? luaL_checknumber(L, 7) : 0;
	
	float angle = (argc >= 8) ? luaL_checknumber(L, 8) : 0.f;
	
	int mode = (argc == 9) ? luaL_checknumber(L, 9) : 0; 
	
	lua_pushnumber(L, InversedText(x, y, font, text, size, angle, color, shadowColor, mode));
	
	return 1;
}

int intraFont_PrintAlphaGradient(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 4 || argc > 10) return luaL_error(L, "font:printAlphaGradient(x,y, text [,size, textColor, gradientColor, gradientMode, angle, alignMode]) must be called with 3, 4, 5, 6, 7, 8 or 9 arguments and must be called with a colon.");
	
	int x = luaL_checkint(L, 2), y = luaL_checkint(L, 3);
	
	intraFont *font = *getintraFont(L, 1);
	if (font == NULL) return luaL_error(L, "intrafont.printAlphaGradient: Error setting font.");
	
	const char *text = luaL_checkstring(L, 4);
	
	float size = (argc >= 5) ? luaL_checknumber(L, 5) : 1.f;
	
	g2dColor color = (argc >= 6) ? luaL_checknumber(L, 6) : 0xFFFFFFFF;
	g2dColor gradientColor = (argc >= 7) ? luaL_checknumber(L, 7) : 0xFF000000;
	
	dMode mode = (argc >= 8) ? luaL_checkint(L, 8) : 4;
	
	float angle = (argc >= 9) ? luaL_checknumber(L,9) : 0.f;
	
	int alignMode = (argc == 10) ? luaL_checknumber(L, 10) : 0; 
	
	if (mode < 0 || mode > 7)
		return luaL_error(L, "intraFont.printAlphaGradient: mode must be either intraFont.G_UP, intraFont.G_LEFT, intraFont.G_RIGHT, intraFont.G_DOWN, intraFont.G_UP_LEFT, intraFont.G_UP_RIGHT, intraFont.G_DOWN_LEFT or intraFont.G_DOWN_RIGHT.");
	
	
	lua_pushnumber(L, AlphaDegrade(x, y, font, text, color, gradientColor, size, angle, alignMode, mode));
	
	return 1;
}


int intraFont_PrintShadowed(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 4 || argc > 10) return luaL_error(L, "font:printDroppedShadow(x,y, text [,size, textColor, shadowColor, intensity, angle, alignMode]) must be called with 3, 4, 5, 6, 7, 8 or 9 arguments and must be called with a colon.");
	
	int x = luaL_checkint(L, 2), y = luaL_checkint(L, 3);
	
	intraFont *font = *getintraFont(L, 1);
	if (font == NULL) return luaL_error(L, "intrafont.printDroppedShadow: Error setting font.");
	
	const char *text = luaL_checkstring(L, 4);
	
	float size = (argc >= 5) ? luaL_checknumber(L, 5) : 1.f;
	
	g2dColor color = (argc >= 6) ? luaL_checknumber(L, 6) : 0xFFFFFFFF;
	g2dColor shadowColor = (argc >= 7) ? luaL_checknumber(L, 7) : 0xFF000000;
	
	char intensity = (argc >= 8) ? luaL_checkint(L, 8) : 30;
	
	float angle = (argc >= 9) ? luaL_checknumber(L,9) : 0.f;
	
	int alignMode = (argc == 10) ? luaL_checknumber(L, 10) : 0; 
	
	lua_pushnumber(L, ShadowedText(x, y, font, text, size, angle, color, shadowColor, alignMode, intensity));
	return 1;
}

int intraFont_PrintBackgrounded(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 4 || argc > 8) return luaL_error(L, "font:printBackgrounded(x,y, text [,size, textColor, backgroundColor, alignMode]) must be called with 3, 4, 5, 6 or 7 arguments and must be called with a colon.");
	
	int x = luaL_checkint(L, 2), y = luaL_checkint(L, 3);
	
	intraFont *font = *getintraFont(L, 1);
	if (font == NULL) return luaL_error(L, "intrafont.printBackgrounded: Error setting font.");
	
	const char *text = luaL_checkstring(L, 4);
	
	float size = (argc >= 5) ? luaL_checknumber(L, 5) : 1.f;
	
	g2dColor color = (argc >= 6) ? luaL_checknumber(L, 6) : 0xFFFFFFFF;
	g2dColor backgroundColor = (argc >= 7) ? luaL_checknumber(L, 7) : 0xFF000000;
	
	int alignMode = (argc == 8) ? luaL_checknumber(L, 8) : 0; 
	
	lua_pushnumber(L, BackgroundColorText(x, y, font, text, size, color, backgroundColor, alignMode));
	return 1;
}

int intraFont_PrintStriked(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 4 || argc > 8) return luaL_error(L, "font:printStriked(x,y, text [,size, color, lineColor, alignMode]) must be called with 3, 4, 5, 6 or 7 arguments and must be called with a colon.");
	
	int x = luaL_checkint(L, 2) , y = luaL_checkint(L, 3);
	
	intraFont *font = *getintraFont(L, 1);
	if (font == NULL) return luaL_error(L, "intrafont.printStriked: Error setting font.");
	
	const char *text = luaL_checkstring(L, 4);
	
	float size = (argc >= 5) ? luaL_checknumber(L, 5) : 1.f;
	
	g2dColor color = (argc >= 6) ? luaL_checknumber(L, 6) : 0xFFFFFFFF;
	g2dColor lineColor = (argc >= 7) ? luaL_checknumber(L, 7) : 0xFF000000;
	
	int alignMode = (argc == 8) ? luaL_checknumber(L, 8) : 0; 
	
	lua_pushnumber(L, StrikedText(x, y, font, text, size, 0, color, lineColor, alignMode));
	return 1;
}


int intraFont_free(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "intraFont.unload(font): wrong number of arguments");
	intraFontUnload(*getintraFont(L, 1));
	
	return 0;
}

int intraFont_tostring(lua_State *L)
{
	lua_pushfstring(L, "intraFont: %p", getintraFont(L, 1));
	return 1;
}


int intraFont_init(lua_State *L)
{
	intraFontInit();
	
	UserdataRegister("intraFont", intraFont_methods, intraFont_metamethods)
	
	lua_pushstring(L, "intraFont");
	lua_gettable(L, LUA_GLOBALSINDEX);
	
	intraFont_Const("CENTER", INTRAFONT_ALIGN_CENTER)
	intraFont_Const("LEFT", INTRAFONT_ALIGN_LEFT)
	intraFont_Const("RIGHT", INTRAFONT_ALIGN_RIGHT)
	
	intraFont_Const("G_UP", GRAD_UP)
	intraFont_Const("G_RIGHT", GRAD_RIGHT)
	intraFont_Const("G_DOWN", GRAD_DOWN)
	intraFont_Const("G_LEFT", GRAD_LEFT)
	intraFont_Const("G_UP_LEFT", GRAD_UP_LEFT)
	intraFont_Const("G_UP_RIGHT", GRAD_UP_RIGHT)
	intraFont_Const("G_DOWN_LEFT", GRAD_DOWN_LEFT)
	intraFont_Const("G_DOWN_RIGHT", GRAD_DOWN_RIGHT)
	
	return 1;
}
