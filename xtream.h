/*
 *	XtreamLua Player - Final Version
 *	xtream.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#ifndef __XLP_XTREAM__
#define __XLP_XTREAM__

#include "common.h"
#include <psprtc.h>
#include <pspdisplay.h>

#include <png.h>



/*
	Xtream.waitVblankStart([count]) - Wait for the vertical blank start before starting drawing.
 
		%arg number [count] The number of time to wait for the VblankStart, default: 1.
 
		%ret nothing
*/

int XT_waitVblankStart(lua_State *L);


/*
	Xtream.exitGame() - Exit the game and go back to the XMB.
		
		%arg nothing
 
		%ret nothing
*/

int XT_exitGame(lua_State *L);


/*
	Xtream.delay(time) - Delay the PSP for a chosen time.
 
		%arg number time The time to delay the PSP, in milliseconds.
 
		%ret nothing
 */

int XT_delay(lua_State *L);


/*
	Xtream.print(x, y, text [,color]) - Print a text with the default intrafont font, ltn8.pgf.
 
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg color [color] The color to print the text, dafault: white.
 
		%ret number The X-coordinate of the last character.
 */

int XT_print(lua_State *L);

/*
	Xtream.debugPrint(x, y, text [,color]) - Print a text with the default PSP font.
 
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg color [color] The color to print the text, dafault: white.
 
		%ret nothing
 */

int XT_debugPrint(lua_State *L);


/*
	Xtream.getFPS() - Get the current number of frames per second.
 
		%ret number The current number of FPS.
 */
int XT_getFPS(lua_State *L);


/*
	Xtream.screenshot(path) - Make a screenshot in png format.
 
		%arg string path The path to save the screen (might end with ".png")
 
		%ret nothing.
 */

int XT_screenshot(lua_State *L);


// XLP internal code //
intraFont *luaFont; //Font used for Xtream.print

double lua_current_time;
double lua_last_time;
int lua_n_fps;
int lua_fps;
u64 lua_tick;

int Xtream_init(lua_State *L);

static const luaL_reg XT_methods[] = { // Xtream methods
	{"waitVblankStart", XT_waitVblankStart},
	{"print", XT_print},
	{"debugPrint", XT_debugPrint},
	{"delay", XT_delay},
	{"getFPS", XT_getFPS},
	{"screenshot", XT_screenshot},
	{"exitGame", XT_exitGame},
	{0,0}
};

#endif

//EOF
