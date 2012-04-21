/*
 *	XtreamLua Player - Final Version
 *	aalib.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#include "aalib.h"

int Aalib_load(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 2 && argc != 3) return luaL_error(L, "Aalib.load(songpath, channel [,loadToRam]): takes 2 or 3 arguments.");
	
	const char *path = luaL_checkstring(L, 1);
	
	int channel = luaL_checkint(L, 2); 
	
	if (channel < PSPAALIB_CHANNEL_SCEMP3_1 || channel > PSPAALIB_CHANNEL_WAV_32)
		return luaL_error(L, "Aalib.load: channel isn't an available channel.");
	
	
	lua_gc(L, LUA_GCCOLLECT, 0);
	
	if (AalibLoad((char*)path, channel, argc == 3 ? (lua_toboolean(L, 3)) : false) != 0) // If channel is a wav sound, load it in RAM, otherwise, don't load it in RAM
		return luaL_error(L, "Aalib.load: Error loading sound.");
	
	return 0;	
}

int Aalib_play(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1 && argc != 2) return luaL_error(L, "Aalib.play(channel [,loop]): takes 1 or 2 arguments.");
	
	AalibSetAutoloop(luaL_checkint(L, 1), argc == 1 ? false : lua_toboolean(L, 2));
	
	if (AalibPlay(luaL_checkint(L, 1)) != 0)
		return luaL_error(L, "Aalib.play: Error playing music.");
	
	return 0;
}

int Aalib_pause(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Aalib.pause(channel): takes 1 argument.");
	
	if (AalibPause(luaL_checkint(L, 1)) != 0)
		return luaL_error(L, "Aalib.pause: Error pausing music.");
	
	return 0;
}

int Aalib_rewind(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Aalib.rewind(channel): takes 1 argument.");
	
	if (AalibRewind(luaL_checkint(L, 1)) != 0)
		return luaL_error(L, "Aalib.rewind: Error rewinding music.");
	
	return 0;
}

int Aalib_stop(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Aalib.stop(channel): takes 1 argument.");
	
	if (AalibStop(luaL_checkint(L, 1)) != 0)
		return luaL_error(L, "Aalib.stop: Error stoping music.");
	
	return 0;
}

int Aalib_setVolume(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 1 || argc > 3) return luaL_error(L, "Aalib.setVolume(channel, left, right): takes 3 arguments.");
	
	AalibVolume volume = {(float)setInterval(luaL_checkint(L, 2), 0, 100) / 100, (float)setInterval(luaL_checkint(L, 3), 0, 100) / 100};
	
	AalibEnable(luaL_checkint(L, 1), PSPAALIB_EFFECT_VOLUME_MANUAL);
	
	if (AalibSetVolume(luaL_checkint(L, 1), volume) != 0)
		return luaL_error(L, "Aalib.stop: Error setting music volume.");
	
	return 0;
}

int Aalib_forward(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 1 || argc > 2) return luaL_error(L, "Aalib.forward(channel, speed): takes 2 arguments.");
	
	AalibEnable(luaL_checkint(L, 1), PSPAALIB_EFFECT_PLAYSPEED);
	
	if (AalibSetPlaySpeed(luaL_checkint(L, 1), setInterval(luaL_checknumber(L, 2), 0.1, 50)) != 0)
		return luaL_error(L, "Aalib.forward: Error forwarding music.");
	
	return 0;
}

int Aalib_unload(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc != 1) return luaL_error(L, "Aalib.unload(channel): takes 1 argument.");
	
	if (AalibUnload(luaL_checkint(L, 1)) != 0)
		return luaL_error(L, "Aalib.unload: Error unloading music.");
	
	return 0;
}

int Aalib_init(lua_State *L)
{	
	if (AalibInit() == 0)
		return 0;
	
	luaL_register(L, "Aalib", Aalib_functions);
	
	lua_pushstring(L, "Aalib");
	lua_gettable(L, LUA_GLOBALSINDEX);
	
	Const("MP3_1", PSPAALIB_CHANNEL_SCEMP3_1)
	Const("MP3_2", PSPAALIB_CHANNEL_SCEMP3_2)
	
	Const("AT3_1", PSPAALIB_CHANNEL_AT3_1)
	Const("AT3_2", PSPAALIB_CHANNEL_AT3_2)
	
	Const("OGG_1", PSPAALIB_CHANNEL_OGG_1)
	Const("OGG_2", PSPAALIB_CHANNEL_OGG_2)
	Const("OGG_3", PSPAALIB_CHANNEL_OGG_3)
	Const("OGG_4", PSPAALIB_CHANNEL_OGG_4)
	Const("OGG_5", PSPAALIB_CHANNEL_OGG_5)
	Const("OGG_6", PSPAALIB_CHANNEL_OGG_6)
	Const("OGG_7", PSPAALIB_CHANNEL_OGG_7)
	Const("OGG_8", PSPAALIB_CHANNEL_OGG_8)
	Const("OGG_9", PSPAALIB_CHANNEL_OGG_9)
	Const("OGG_10", PSPAALIB_CHANNEL_OGG_10)
	
	Const("WAV_1", PSPAALIB_CHANNEL_WAV_1)
	Const("WAV_2", PSPAALIB_CHANNEL_WAV_2)
	Const("WAV_3", PSPAALIB_CHANNEL_WAV_3)
	Const("WAV_4", PSPAALIB_CHANNEL_WAV_4)
	Const("WAV_5", PSPAALIB_CHANNEL_WAV_5)
	Const("WAV_6", PSPAALIB_CHANNEL_WAV_6)
	Const("WAV_7", PSPAALIB_CHANNEL_WAV_7)
	Const("WAV_8", PSPAALIB_CHANNEL_WAV_8)
	Const("WAV_9", PSPAALIB_CHANNEL_WAV_9)
	Const("WAV_10", PSPAALIB_CHANNEL_WAV_10)
	Const("WAV_11", PSPAALIB_CHANNEL_WAV_11)
	Const("WAV_12", PSPAALIB_CHANNEL_WAV_12)
	Const("WAV_13", PSPAALIB_CHANNEL_WAV_13)
	Const("WAV_14", PSPAALIB_CHANNEL_WAV_14)
	Const("WAV_15", PSPAALIB_CHANNEL_WAV_15)
	Const("WAV_16", PSPAALIB_CHANNEL_WAV_16)
	Const("WAV_17", PSPAALIB_CHANNEL_WAV_17)
	Const("WAV_18", PSPAALIB_CHANNEL_WAV_18)
	Const("WAV_19", PSPAALIB_CHANNEL_WAV_19)
	Const("WAV_20", PSPAALIB_CHANNEL_WAV_20)
	Const("WAV_21", PSPAALIB_CHANNEL_WAV_21)
	Const("WAV_22", PSPAALIB_CHANNEL_WAV_22)
	Const("WAV_23", PSPAALIB_CHANNEL_WAV_23)
	Const("WAV_24", PSPAALIB_CHANNEL_WAV_24)
	Const("WAV_25", PSPAALIB_CHANNEL_WAV_25)
	Const("WAV_26", PSPAALIB_CHANNEL_WAV_26)
	Const("WAV_27", PSPAALIB_CHANNEL_WAV_27)
	Const("WAV_28", PSPAALIB_CHANNEL_WAV_28)
	Const("WAV_29", PSPAALIB_CHANNEL_WAV_29)
	Const("WAV_30", PSPAALIB_CHANNEL_WAV_30)
	Const("WAV_31", PSPAALIB_CHANNEL_WAV_31)
	Const("WAV_32", PSPAALIB_CHANNEL_WAV_32)
	
	return 1;
}

// EOF
