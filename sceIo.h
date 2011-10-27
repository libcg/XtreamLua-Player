/*
 *	XtreamLua Player - Final Version
 *	sceIo.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#ifndef __XLP_SCEIO__
#define __XLP_SCEIO__

#include "common.h"


/*
	sceIo.rename(oldFileName, newFileName) - Rename a file.
 
		%arg string oldFileName The file path that will be renamed.
		%arg string newFileName The new name of the file, after renaming.
 
		%ret error An error if the file couldn't have been renamed.
*/

int sceIo_rename(lua_State *L);


/*
	sceIo.remove(path) - Remove a file or an EMPTY directory.
 
		%arg string path The path of the file or the empty directory to be removed.
 
		%ret error An error if the file or directory couldn't have been removed.
*/

int sceIo_remove(lua_State *L);


/*
	sceIo.createDirectory(path) - Create an empty directory.
 
		%arg string path The path of the created directory.
 
		%ret error An error if the directory couldn't have been created.
*/

int sceIo_createDirectory(lua_State *L);


/*
	sceIo.currentDirectory([newDirectory]) - Get and/or Set the current directory of the program.
 
		%arg string [newDirectory] The directory that will be taken as the current directory, default: doesn't set a new current directory.
 
		%ret string The (new) current directory.
*/

int sceIo_currentDirectory(lua_State *L);


/*
	sceIo.listDirectory([directory]) - List the content of a directory.
 
		%arg string [directory] The directory which will be listed, default: the current directory will be listed.
 
		%ret table A table containing all elements in the directory, like this: dir = sceIo.listDirectory() => dir[1].name (string), dir[1].isDirectory (boolean) and size (number).
*/

int sceIo_listDirectory(lua_State *L);


// XLP internal code //
int sceIo_init(lua_State *L);

bool isDirectory(const char *path);

static const luaL_reg sceIo_methods[] = {
	{"rename", sceIo_rename},
	{"remove", sceIo_remove},
	{"createDirectory", sceIo_createDirectory},
	{"currentDirectory", sceIo_currentDirectory},
	{"listDirectory", sceIo_listDirectory},
	{0,0}
};


#endif

//EOF
