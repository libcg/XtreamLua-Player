/*
 *	XtreamLua Player - Final Version
 *	xtream.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#include "xtream.h"

int XT_waitVblankStart(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 0 && argc != 1) 
		return luaL_error(L, "Xtream.waitVblankStart([count]): takes zero or one argument");
	
	if ((argc == 1) && (lua_type(L, 1) == LUA_TNUMBER))
	{
		int i;
		for (i = 0; i < luaL_checkint(L, 1); i++)
			sceDisplayWaitVblankStart();
	}
	else 
		sceDisplayWaitVblankStart();
	
	return 0;
}

int XT_exitGame(lua_State *L)
{
	sceKernelExitGame();
	return 0;
}

int XT_delay(lua_State *L)
{
	if (lua_gettop(L) != 1) 
		return luaL_error(L, "Xtream.delay(millisec): wrong number of arguments");
	
	sceKernelDelayThread(luaL_checkint(L, 1) * 1000);
	
	return 0;
}

int XT_print(lua_State *L)
{	
	int argc = lua_gettop(L);
	if (argc < 3 || argc > 4) 
		return luaL_error(L, "Xtream.print(x,y,text [,color]): wrong number of arguments");
	
	int posx = luaL_checkint(L, 1);
	int posy = luaL_checkint(L, 2) + 10;
	
	intraFontSetStyle(luaFont, 0.9f, argc == 3 ? 0xFFFFFFFF : luaL_checknumber(L, 4), 0, 0, INTRAFONT_ALIGN_LEFT);
	
	lua_pushnumber(L, intraFontPrint(luaFont, posx, posy, luaL_checkstring(L, 3)));
	
	return 1;
}

int XT_debugPrint(lua_State *L)
{	
	int argc = lua_gettop(L);
	if (argc != 3 && argc != 4) 
		return luaL_error(L, "Xtream.debugPrint(x,y,text [,color]): wrong number of arguments");
	
	int posx = luaL_checkint(L, 1);
	int posy = luaL_checkint(L, 2);

	int n;	
	const char *buff = luaL_checkstring(L, 3);
	
	g2dColor color = (argc == 4) ? luaL_checknumber(L, 4) : 0xFFFFFFFF;

	for (n = 0; n < strlen(buff); n++)
		pspDebugScreenPutChar(posx + 7*n, posy, color, buff[n]);

	return 0;
}


int XT_getFPS(lua_State *L)
{	
	lua_n_fps++;	
    sceRtcGetCurrentTick(&lua_tick);
	
    lua_current_time = lua_tick/1000;
	
    if ((lua_current_time - lua_last_time) >= 1000)
    {
		lua_fps = lua_n_fps;
		lua_n_fps = 0;
		lua_last_time = lua_current_time;
    }
	
	lua_pushnumber(L, lua_fps);
	
	return 1;
}

int XT_screenshot(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Xtream.screenshot(path): takes 1 argument.");
	
	FILE *file = fopen(luaL_checkstring(L, 1), "wb");
	
	if (file == NULL)
		return luaL_error(L, "Xtream.screenshot(path): Cannot create/open path file.");
	
	png_structp png_ptr;
	png_infop info_ptr;
	int i, x, y;
	u8* line;
	
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) return luaL_error(L, "Xtream.savescreen: Error creating file's write strcture.");;
	
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) 
	{
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return luaL_error(L, "Xtream.savescreen: Error creating file's info strcture.");
	}
	
	png_init_io(png_ptr, file);
	
	png_set_IHDR(png_ptr, info_ptr, g2d_disp_buffer.w, g2d_disp_buffer.h, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);
	
	line = (u8*) malloc(480 * 3); // 3 = R, G and B. Alpha isn't needed, save screen, not a texture.
	
	for (y = 0; y < g2d_disp_buffer.h; y++)
	{
		i = 0;
		for (x = 0; x < g2d_disp_buffer.w; x++)
		{
			g2dColor color = g2d_disp_buffer.data[x + y * 512];
			
			line[i++] = G2D_GET_R(color);
			line[i++] = G2D_GET_G(color);
			line[i++] = G2D_GET_B(color);
		}
		png_write_row(png_ptr, line);
	}
	
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	
	free(line);
	fclose(file);
	
	return 0;
}


int Xtream_init(lua_State *L)
{
	luaFont = intraFontLoad("flash0:/font/ltn8.pgf", INTRAFONT_CACHE_ASCII); //Loads font used for Xtream.print
	
	if (luaFont == NULL)
		return 0;
	
	//FPS init
		lua_current_time = 0;
		lua_last_time = 0;
		lua_n_fps = 0;
		lua_fps = 60;
	
	luaL_register(L, "Xtream", XT_methods);
	
	return 1;
}

//EOF
