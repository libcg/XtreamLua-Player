#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <string.h>
#include <stdio.h>
#include <psputility.h>
#include <malloc.h>
#include <math.h>

#include <pspgu.h>
#include <pspgum.h>

#include "savedata.h"

#define DATABUFFLEN 0x20

PspUtilitySavedataListSaveNewData luaData;

char nameMultiple[][20] =
{
	"0000",
	"0001",
	"0002",
	"0003",
	"0004",
	""
};

char key[] = "QTAK319JQKJ952HA";	// Key to encrypt or decrypt savedata

void initSavedata(SceUtilitySavedataParam * savedata, int mode, const char *title, const char *data)
{
	memset(savedata, 0, sizeof(SceUtilitySavedataParam));
	savedata->base.size = sizeof(SceUtilitySavedataParam);
	
	savedata->base.language = PSP_SYSTEMPARAM_LANGUAGE_ENGLISH;
	savedata->base.buttonSwap = PSP_UTILITY_ACCEPT_CROSS;
	savedata->base.graphicsThread = 0x11;
	savedata->base.accessThread = 0x13;
	savedata->base.fontThread = 0x12;
	savedata->base.soundThread = 0x10;
	
	savedata->mode = mode;
	savedata->overwrite = 1;
	savedata->focus = PSP_UTILITY_SAVEDATA_FOCUS_LATEST; // Set initial focus to the newest file (for loading)
	
#if _PSP_FW_VERSION >= 200
	strncpy(savedata->key, key, 16);
#endif
	
	strcpy(savedata->gameName, title);	// First part of the save name, game identifier name
	strcpy(savedata->saveName, "0000");	// Second part of the save name, save identifier name
	
	// List of multiple names
	savedata->saveNameList = nameMultiple;
	
	strcpy(savedata->fileName, "DATA.BIN");
	
	// Allocate buffers used to store various parts of the save data
	savedata->dataBuf = malloc(DATABUFFLEN);
	savedata->dataBufSize = DATABUFFLEN;
	savedata->dataSize = DATABUFFLEN;
	
	if (mode == PSP_UTILITY_SAVEDATA_LISTSAVE)
	{
		memset(savedata->dataBuf, 0, DATABUFFLEN);
		strcpy(savedata->dataBuf, data);
		
		strcpy(savedata->sfoParam.title, title);
		strcpy(savedata->sfoParam.savedataTitle, title);
		strcpy(savedata->sfoParam.detail, "XtreamLua Player Savedata");
		savedata->sfoParam.parentalLevel = 1;
		
		savedata->icon1FileData.buf = NULL;
		savedata->icon1FileData.bufSize = 0;
		savedata->icon1FileData.size = 0;
		
		savedata->icon1FileData.buf = NULL;
		savedata->icon1FileData.bufSize = 0;
		savedata->icon1FileData.size = 0;
		
		savedata->pic1FileData.buf = NULL;
		savedata->pic1FileData.bufSize = 0;
		savedata->pic1FileData.size = 0;
		
		savedata->icon0FileData.buf = NULL;
		savedata->icon0FileData.bufSize = 0;
		savedata->icon0FileData.size = 0;
		
		savedata->snd0FileData.buf = NULL;
		savedata->snd0FileData.bufSize = 0;
		savedata->snd0FileData.size = 0;
		
		luaData.title = "New Data";
		
		savedata->newData = &luaData;
		
		savedata->focus = PSP_UTILITY_SAVEDATA_FOCUS_FIRSTEMPTY;
	}
}


char *showSavedataDialog(int mode, const char *title, const char *data)
{
	SceUtilitySavedataParam dialog;
    initSavedata(&dialog, mode, title, data);
	
    sceUtilitySavedataInitStart(&dialog);	
	
	int done = 0;
	
    while(!done) 
	{
		g2dClear(0xFF554433);
		sceGuFinish();
		sceGuSync(0,0);
		
		switch(sceUtilitySavedataGetStatus()) 
		{				
			case PSP_UTILITY_DIALOG_VISIBLE:
				sceUtilitySavedataUpdate(1);
				break;
				
			case PSP_UTILITY_DIALOG_QUIT:
				sceUtilitySavedataShutdownStart();
				break;
				
			case PSP_UTILITY_DIALOG_FINISHED:
				
			case PSP_UTILITY_DIALOG_NONE:
				done = 1;
				break;
		}
		
		g2dFlip(G2D_SWIZZLE);
    }

	return (char*)dialog.dataBuf;
}

int Savedata_load(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Savedata.load(gameName): takes one argument.");
	
	if (lua_type(L, 1) != LUA_TSTRING)
		return luaL_error(L, "Savedata.load(gameName): gameName must be a string.");
	
	lua_pushstring(L, showSavedataDialog(PSP_UTILITY_SAVEDATA_LISTLOAD, luaL_checkstring(L, 1), NULL));
	
	return 1;
}

int Savedata_save(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 2) return luaL_error(L, "Savedata.save(gameName, saveData): takes 1, 2, 3 or 4 arguments.");
	
	if (lua_type(L, 1) != LUA_TSTRING)
		return luaL_error(L, "Savedata.save(gameName, saveData): gameName must be a string.");
	
	if (lua_type(L, 2) != LUA_TSTRING)
		return luaL_error(L, "Savedata.save(gameName, saveData): saveData must be a string.");
	
	showSavedataDialog(PSP_UTILITY_SAVEDATA_LISTSAVE, luaL_checkstring(L, 1), luaL_checkstring(L, 2));
	
	return 0;
}


static const luaL_reg Savedata_methods[] = {
	{"load", Savedata_load},
	{"save", Savedata_save},
	{0,0}
};

void Savedata_init(lua_State *L)
{
	luaL_openlib(L, "Savedata", Savedata_methods, 0);	
}


