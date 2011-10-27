/*
 *	XtreamLua Player - Final Version
 *	sceIo.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#include "sceIo.h"
#include <unistd.h>

bool isDirectory(const char *path) //seems to be not working every time with sceIo.listDirectory()
{
	int fd = sceIoDopen(path);
	
	if (fd >= 0)
	{
		sceIoDclose(fd);
		return true;
	}
	
	return false;
}


int sceIo_rename(lua_State *L)
{
	if (lua_gettop(L) != 2) return luaL_error(L, "sceIo.rename(oldfilename, newfilename): takes two arguments.");
	
	if (sceIoRename(luaL_checkstring(L, 1), luaL_checkstring(L, 2)) < 0)
		return luaL_error(L, "sceIo.rename: Error renaming file, please check it's present.");
	
	return 0;
}

int sceIo_remove(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "sceIo.remove(path): takes one argument.");
	
	if (isDirectory(luaL_checkstring(L, 1)))
	{
		if (sceIoRmdir(luaL_checkstring(L, 1)) < 0)
			return luaL_error(L, "sceIo.remove: Error removing directory.");
	}
	else
	{
		if (sceIoRemove(luaL_checkstring(L, 1)) < 0)
			return luaL_error(L, "sceIo.remove: Error removing file.");
	}
	
	return 0;
}

int sceIo_createDirectory(lua_State *L)
{
	if (lua_gettop(L) != 1) return luaL_error(L, "sceIo.createDir(path): takes one argument.");
	
	if (sceIoMkdir(luaL_checkstring(L, 1), 0777) < 0)
		return luaL_error(L, "sceIo.createDirectory: Error creating directory.");
		
	return 0;
}

int sceIo_currentDirectory(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 0 || argc > 1) return luaL_error(L, "sceIo.currentDirectory([newDirectory]): takes 0 or 1 argument.");
	
	char directory[256];
	getcwd(directory, 256);
	lua_pushstring(L, directory);
	
	if (argc)
		chdir(luaL_checkstring(L, 1));
	
	return 1;
}

SceIoDirent dir;
int sceIo_listDirectory(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 0 || argc > 1) return luaL_error(L, "sceIo.listDirectory([directory]): takes zero or one argument.");
	
	int fd = sceIoDopen(argc == 1 ? luaL_checkstring(L, 1) : "");
	
	if (fd < 0) 
		return luaL_error(L, "sceIo.listDirectory: error listing directory, please check it's present.");
	
	int i;
	lua_newtable(L);
	
	for (i = 1; sceIoDread(fd, &dir) > 0; i++)
	{
		lua_pushinteger(L, i);
		
		lua_newtable(L);
		lua_pushstring(L, "name");
		lua_pushstring(L, dir.d_name);
		lua_settable(L, -3);
		
		lua_pushstring(L, "size");
		lua_pushnumber(L, dir.d_stat.st_size);
		lua_settable(L, -3);
		
		lua_pushstring(L, "isDirectory");
		lua_pushboolean(L, FIO_S_ISDIR(dir.d_stat.st_mode));
		lua_settable(L, -3);
		
		lua_settable(L, -3);
	}
	
	sceIoDclose(fd);
	
	return 1;
}




int sceIo_init(lua_State *L)
{
	luaL_openlib(L, "sceIo", sceIo_methods, 0);
	
	return 1;
}

//EOF
