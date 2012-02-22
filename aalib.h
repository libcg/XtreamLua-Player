/*
 *	XtreamLua Player - Final Version
 *	aalib.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#ifndef __XLP_AALIB__
#define __XLP_AALIB__

#include "common.h"


/*
	Aalib.load(songpath, channel) - Load a song. Allowed formats: .mp3 .ogg .wav .at3
 
		%arg string songpath The path a the music file to load.
		%arg number channel The channel of the new song. Channels: Aalib.MP3_1, Aalib.MP3_2, Aalib.WAV_1 -> Aalib.WAV_32, Aalib.OGG_1 -> Aalib.OGG_10, Aalib.AT3_1, Aalib.AT3_2.

		%ret error An error if the music couldn't have been loaded.
 */

int Aalib_load(lua_State *L);


/*
	Aalib.play(channel [,loop]) - Play a song.
 
		%arg number channel The channel to play.
		%arg boolean [loop] Pass true to play the song in a loop, or false to play it once, default: false.
 
		%ret error An error if the music couldn't have been played.
 */

int Aalib_play(lua_State *L);


/*
	Aalib.pause(channel) - Pause a song.
 
		%arg number channnel The channel to pause.
 
		%ret error An error if the music couldn't have been paused.
 */

int Aalib_pause(lua_State *L);


/*
	Aalib.rewind(channel) - Rewind a song. WARNING: Seem to frezze the PSP if too many rewinds are required.
 
		%arg number channel The channel to rewind.
 
		%ret error An error if the music couldn't have been rewinded.
 */

int Aalib_rewind(lua_State *L);


/*
	Aalib.stop(channel) - Stop a song. WARNING: Seem to frezze the PSP if too many stops are required (because stop calls a rewind).
 
		%arg number channel The channel to stop.
 
		%ret error An error if the music couldn't have been stopped.
 */

int Aalib_stop(lua_State *L);


/*
	Aalib.setVolume(channel, left, right) - Set the left and right volume of a song.
 
		%arg number channel The channel which you want to change the volume.
		%arg number left The left speaker's volume to set, between 0 -> 100.
		%arg number right The right speaker's volume to set, between 0 -> 100.
 
		%ret error An error if the volume couldn't have been changed.
 */

int Aalib_setVolume(lua_State *L);


/*
	Aalib.forward(channel, speed) - Forward a song.
 
		%arg number channel The channel to forward.
		%arg number speed The speed with wich one the song will be forwarded, between 0.1 -> 50.
 
		%ret error An error if the music couldn't have been forwarded.
 */

int Aalib_forward(lua_State *L);


/*
	Aalib.unload(channel) - Unload a song.
 
		%arg number channel The channel to unload.
 
		%ret error An error if the music couldn't have been unloaded.
 */

int Aalib_unload(lua_State *L);



// XLP internal code //
int Aalib_init(lua_State *L);

static const luaL_Reg Aalib_functions[] = { // Aalib methods
	{"load", Aalib_load},
	{"unload", Aalib_unload},
	{"play", Aalib_play},
	{"pause", Aalib_pause},
	{"rewind", Aalib_rewind},
	{"stop", Aalib_stop},
	{"setVolume", Aalib_setVolume},
	{"forward", Aalib_forward},
	{0,0}
};

#endif

//EOF
