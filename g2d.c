/*
 *	XtreamLua Player - Final Version
 *	g2d.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#include "g2d.h"

UserdataConvert(g2d, g2dImage*, "Image")

int g2D_clear(lua_State *L)
{
	if (lua_gettop(L) != 0 && lua_gettop(L) != 1) return luaL_error(L, "g2d.Clear([color]): takes 0 or 1 argument.");
	
	u32 color = lua_gettop(L) == 0 ? 0 : luaL_checknumber(L, 1);
	
	g2dClear(color);
	
	return 0;
}

int g2D_clearZ(lua_State *L)
{
	if (lua_gettop(L) != 0 && lua_gettop(L) != 1) return luaL_error(L, "g2d.ClearZ([color]): takes 0 or 1 argument.");
	
	u32 color = lua_gettop(L) == 0 ? 0 : luaL_checknumber(L, 1);
	
	g2dClearZ(color);
	
	return 0;
}

int g2D_beginRects(lua_State *L)
{
	if (lua_gettop(L) != 0 && lua_gettop(L) != 1) return luaL_error(L, "g2d.BeginRects([texture]): takes 0 or 1 argument.");
	
	if (lua_gettop(L) == 1)
	{
		g2dImage *image = *getg2d(L, 1);
		g2dBeginRects(image);
	}
	else
		g2dBeginRects(NULL);
	
	return 0;
}

int g2D_beginQuads(lua_State *L)
{
	if (lua_gettop(L) != 0 && lua_gettop(L) != 1) return luaL_error(L, "g2d.BeginQuads([texture]): takes 0 or 1 argument.");
	
	if (lua_gettop(L) == 1)
	{
		g2dImage *image = *getg2d(L, 1);
		g2dBeginQuads(image);
	}
	else
		g2dBeginQuads(NULL);
	
	return 0;
}

int g2D_beginLines(lua_State *L)
{
	if (lua_gettop(L) != 0 && lua_gettop(L) != 1) return luaL_error(L, "g2d.BeginLines([line_mode]): takes 0 or 1 argument.");
	
	g2dEnum strip = lua_gettop(L) == 0 ? G2D_VOID : luaL_checkint(L, 1) &G2D_STRIP ? G2D_STRIP : G2D_VOID;
	
	g2dBeginLines(strip);
	
	return 0;
}

int g2D_beginPoints(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "g2d.BeginPoints(): takes no argument.");
	
	g2dBeginPoints();
	
	return 0;
}

int g2D_end(lua_State *L)
{
	g2dEnd();
	
	return 0;
}

int g2D_reset(lua_State *L)
{
	g2dReset();
	
	return 0;
}

int g2D_flip(lua_State *L)
{
	if (lua_gettop(L) != 0 && lua_gettop(L) != 1) return luaL_error(L, "g2d.Flip([vsync]): takes 0 or 1 argument.");
	
	g2dEnum vsync = (lua_gettop(L) == 1 ? G2D_VSYNC : G2D_VOID);
	
	g2dFlip(vsync);
	
	return 0;
}

int g2D_add(lua_State *L)
{
	g2dAdd();
	
	return 0;
}

int g2D_push(lua_State *L)
{
	g2dPush();
	
	return 0;
}

int g2D_pop(lua_State *L)
{
	g2dPop();
	
	return 0;
}

int g2D_texFree(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.TexFree(texture): takes one argument.");
	
	g2dTexFree(getg2d(L,1));
	
	return 0;
}

int g2D_texLoad(lua_State *L)
{
	if (lua_gettop(L) != 1 && lua_gettop(L) != 2) return luaL_error(L, "g2d.TexLoad(path [,swizzle]): takes 1 or 2 arguments.");
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	g2dImage *src = g2dTexLoad((char*)luaL_checkstring(L, 1), lua_gettop(L) == 1 ? G2D_VOID : luaL_checkint(L, 2) &G2D_SWIZZLE ? G2D_SWIZZLE : G2D_VOID);
	if (!src) return luaL_error(L, "g2d.TexLoad: Error loading image.");
	
	g2dImage **image;
	image = pushg2d(L);
	*image = src;
	
	return 1;
}

int g2D_resetCoord(lua_State *L)
{
	g2dResetCoord();
	
	return 0;
}

int g2D_setCoordMode(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetCoordMode(mode): takes one argument.");

	g2dEnum mode = luaL_checkint(L, 1);
	
	if (mode < G2D_UP_LEFT || mode > G2D_CENTER) return luaL_error(L, "g2d.SetCoordMode(mode): mode must be either g2d.UP_LEFT, g2d.UP_RIGHT, g2d.DOWN_LEFT, g2d.DOWN_RIGHT or g2d.CENTER.");
	
	g2dSetCoordMode(mode);
	
	return 0;
}

int g2D_getCoordXYZ(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "g2d.GetCoordXYZ(): takes no argument.");
	
	float x, y, z;
	g2dGetCoordXYZ(&x,&y,&z);
	
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_pushnumber(L, z);
	
	return 3;
}

int g2D_setCoordXY(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetCoordXY(x,y): takes 2 arguments.");
	
	g2dSetCoordXY(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_setCoordXYZ(lua_State *L)
{
	if (lua_gettop(L) != 3) return luaL_error(L, "g2d.SetCoordXYZ(x,y,z): takes 3 arguments.");
	
	g2dSetCoordXYZ(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	
	return 0;
}

int g2D_setCoordXYRelative(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetCoordXYRelative(x,y): takes 2 arguments.");
	
	g2dSetCoordXYRelative(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_setCoordXYZRelative(lua_State *L)
{
	if (lua_gettop(L) != 3) return luaL_error(L, "g2d.SetCoordXYZRelative(x,y,z): takes 3 arguments.");
	
	g2dSetCoordXYZRelative(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	
	return 0;
}

int g2D_resetCrop(lua_State *L)
{
	g2dResetCrop();
	
	return 0;
}

int g2D_getCropXY(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "g2d.GetCropXY(): takes no argument.");
	
	int x, y;
	g2dGetCropXY(&x,&y);
	
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	
	return 2;
}

int g2D_getCropWH(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "g2d.GetCropWH(): takes no argument.");
	
	int w, h;
	g2dGetCropWH(&w,&h);
	
	lua_pushnumber(L, w);
	lua_pushnumber(L, h);
	
	return 2;
}

int g2D_setCropXY(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetCropXY(x,y): takes 2 arguments.");
	
	g2dSetCropXY(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_setCropWH(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetCropWH(w,h): takes 2 arguments.");
	
	g2dSetCropWH(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_setCrop(lua_State *L)
{
	if (lua_gettop(L) != 4) return luaL_error(L, "g2d.SetCrop(x,y,w,h): takes 4 arguments.");
	
	g2dSetCropXY(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	g2dSetCropWH(luaL_checknumber(L, 3), luaL_checknumber(L, 4));
	
	return 0;
}

int g2D_setCropXYRelative(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetCropXYRelative(x,y): takes 2 arguments.");
	
	g2dSetCropXYRelative(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_setCropWHRelative(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetCropWHRelative(w,h): takes 2 arguments.");
	
	g2dSetCropWHRelative(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_setCropRelative(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetCropRelative(x,y,w,h): takes 4 arguments.");
	
	g2dSetCropXYRelative(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	g2dSetCropWHRelative(luaL_checknumber(L, 3), luaL_checknumber(L, 4));
	
	return 0;
}

int g2D_resetScale(lua_State *L)
{
	g2dResetScale();
	
	return 0;
}

int g2D_getScale(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "g2d.GetScale(): takes no argument.");
	
	float w, h;
	g2dGetScaleWH(&w,&h);
	
	lua_pushnumber(L, w);
	lua_pushnumber(L, h);
	
	return 2;
}

int g2D_setScale(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetScale(w,h): takes 2 arguments.");
	
	g2dSetScale(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_setScaleWH(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetScaleWH(w,h): takes 2 arguments.");
	
	g2dSetScaleWH(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_setScaleRelative(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetScaleRelative(w,h): takes 2 arguments.");
	
	g2dSetScaleRelative(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_setScaleWHRelative(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "g2d.SetScaleWHRelative(w,h): takes 2 arguments.");
	
	g2dSetScaleWHRelative(luaL_checknumber(L, 1), luaL_checknumber(L, 2));
	
	return 0;
}

int g2D_resetColor(lua_State *L)
{
	g2dResetColor();
	
	return 0;
}

int g2D_resetAlpha(lua_State *L)
{
	g2dResetAlpha();
	
	return 0;
}

int g2D_getAlpha(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "g2d.GetAlpha(): takes no argument.");
	
	g2dAlpha alpha;
	g2dGetAlpha(&alpha);
	
	lua_pushinteger(L, alpha);
	
	return 1;
}

int g2D_setColor(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetColor(color): takes one argument.");
	
	g2dSetColor(luaL_checknumber(L, 1));
	
	return 0;
}

int g2D_setAlpha(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetAlpha(alpha): takes one argument.");
	
	g2dSetAlpha(0);
	g2dSetAlpha(luaL_checkint(L, 1));
	
	return 0;
}

int g2D_setAlphaRelative(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetAlphaRelative(alpha): takes one argument.");

	g2dSetAlphaRelative(luaL_checkint(L, 1));
	
	return 0;
}

int g2D_resetRotation(lua_State *L)
{
	g2dResetRotation();
	
	return 0;
}

int g2D_getRotationRad(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "g2d.GetRotationRad(): takes no argument.");
	
	float rad;
	g2dGetRotationRad(&rad);
	
	lua_pushnumber(L, rad);
	
	return 1;
}

int g2D_getRotation(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "g2d.GetRotation(): takes no argument.");
	
	float deg;
	g2dGetRotation(&deg);
	
	lua_pushnumber(L, deg);
	
	return 1;
}

int g2D_setRotationRad(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetRotationRad(angle): takes one argument.");
	
	g2dSetRotationRad(luaL_checknumber(L, 1));
	
	return 0;
}

int g2D_setRotation(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetRotation(angle): takes one argument.");
	
	g2dSetRotation(luaL_checknumber(L, 1));
	
	return 0;
}

int g2D_setRotationRadRelative(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetRotationRadRelative(angle): takes one argument.");
	
	g2dSetRotationRadRelative(luaL_checknumber(L, 1));
	
	return 0;
}

int g2D_setRotationRelative(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetRotationRelative(angle): takes one argument.");
	
	g2dSetRotationRelative(luaL_checknumber(L, 1));
	
	return 0;
}

int g2D_resetTex(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "g2d.ResetTex(): takes no argument.");
	
	g2dResetTex();
	
	return 0;
}

int g2D_setTexRepeat(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetTexRepeat(use): takes one argument (boolean).");
	
	g2dSetTexRepeat(lua_toboolean(L, 1));
	
	return 0;
}

int g2D_setTexBlend(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetTexBlend(use): takes one argument (boolean).");
	
	g2dSetTexBlend(lua_toboolean(L, 1));
	
	return 0;
}

int g2D_setTexLinear(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "g2d.SetTexLinear(use): takes one argument (boolean).");
	
	g2dSetTexLinear(lua_toboolean(L, 1));
	
	return 0;
}

int g2D_resetScissor(lua_State *L)
{
	g2dResetScissor();
	
	return 0;
}

int g2D_setScissor(lua_State *L)
{
	if (lua_gettop(L) != 4) return luaL_error(L, "g2d.SetScissor(x,y,w,h): takes 4 arguments.");
	
	g2dSetScissor(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
	
	return 0;
}

int g2D_getWidth(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "texture:width() takes no argument and must be called with a colon.");
	
	g2dImage *image = *getg2d(L, 1);
	if (image == NULL)
		return luaL_error(L, "texture:width(): cannot get 'texture'.");
	
	lua_pushinteger(L, image->w);
	
	return 1;
}

int g2D_getHeight(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "texture:height() takes no argument and must be called with a colon.");
	
	g2dImage *image = *getg2d(L, 1);
	if (image == NULL)
		return luaL_error(L, "texture:height(): cannot get 'texture'.");
	
	lua_pushinteger(L, image->h);
	
	return 1;
}

int g2D_blit(lua_State *L) //Quick blit function
{
	int argc = lua_gettop(L);
	if (argc != 3) return luaL_error(L, "texture:Blit(x,y): takes 2 arguments and must be called with a colon.");
	
	g2dImage *image = *getg2d(L, 1);
	if (image == NULL)
		return luaL_error(L, "texture:Blit: cannot get 'texture'.");
	
	g2dBeginRects(image);
		g2dSetCoordXY(luaL_checknumber(L, 2), luaL_checknumber(L, 3));	
		g2dAdd();
	g2dEnd();
	
	return 0;
}

int g2D_getPixel(lua_State *L)
{
	if (lua_gettop(L) != 2 && lua_gettop(L) != 3) return luaL_error(L, "g2d.getPixel([texture,] x,y) takes 2 or 3 arguments.");
	
	if (lua_gettop(L) == 3) //If we want to get a texture pixel
	{
		g2dImage *image = *getg2d(L, 1);
		if (image == NULL)
			return luaL_error(L, "texture:getPixel(): cannot set 'texture'.");
	
		if (image->swizzled == true)
			return luaL_error(L, "texture:getPixel(): cannot get pixel on a swizzled texture, please do not swizzle it.");
	
		lua_pushnumber(L, image->data[luaL_checkint(L, 2) + image->tw * luaL_checkint(L, 3)]);
	}
	else
		lua_pushnumber(L, g2d_draw_buffer.data[luaL_checkint(L, 1) + 512 * luaL_checkint(L, 2)]); //Screen pixel
	
	return 1;
}

int g2D_setPixel(lua_State *L)
{
	if (lua_gettop(L) != 3 && lua_gettop(L) != 4) return luaL_error(L, "g2d.setPixel([texture,] x,y,color) takes 3 or 4 arguments.");
	
	g2dColor color = luaL_checknumber(L, 4);
	
	u8 r = setInterval(G2D_GET_R(color), 0, 255);
	u8 g = setInterval(G2D_GET_G(color), 0, 255);
	u8 b = setInterval(G2D_GET_B(color), 0, 255);
	u8 a = setInterval(G2D_GET_A(color), 0, 255);
	
	if (lua_gettop(L) == 4) //If we want to set a texture pixel
	{
		g2dImage *image = *getg2d(L, 1);
		if (image == NULL)
			return luaL_error(L, "texture:setPixel(): cannot set 'texture'.");
		
		if (image->swizzled == true)
			return luaL_error(L, "texture:setPixel(): cannot set pixel on a swizzled texture, please do not swizzle it.");
	
		image->data[luaL_checkint(L, 2) + image->tw * luaL_checkint(L, 3)] = G2D_RGBA(r, g, b, a);
	}
	else
		g2d_draw_buffer.data[luaL_checkint(L, 1) + 512 * luaL_checkint(L, 2)] = G2D_RGBA(r,g,b,a); //Screen pixel
		
	return 1;
}

int g2D_isSwizzled(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "texture:isSwizzled(): takes no argument and must be called with a colon.");
	
		g2dImage *image = *getg2d(L, 1);
		if (image == NULL)
			return luaL_error(L, "texture:isSwizzled(): cannot set 'texture'.");
		
		if (image->swizzled == true)
			lua_pushboolean(L, true);
	
		else
			lua_pushboolean(L, false);
	
	return 1;
}


int g2D_tostring(lua_State *L)
{
	lua_pushfstring(L, "g2dImage: %p", getg2d(L, 1));
	return 1;
}


int g2D_init(lua_State *L)
{	
	UserdataRegister("g2d", g2d_methods, g2d_metamethods)
	
	
	lua_pushstring(L, "g2d");
	lua_gettable(L, LUA_GLOBALSINDEX);
	
	Const("SWIZZLE", G2D_SWIZZLE)
	Const("VSYNC", G2D_VSYNC)
	Const("STRIP", G2D_STRIP)
	
	Const("UP_LEFT", G2D_UP_LEFT)
	Const("UP_RIGHT", G2D_UP_RIGHT)
	Const("DOWN_LEFT", G2D_DOWN_LEFT)
	Const("DOWN_RIGHT", G2D_DOWN_RIGHT)
	Const("CENTER", G2D_CENTER)
	
	return 1;
}

// EOF
