/*
 *	XtreamLua Player - Final Version
 *	utility.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#ifndef __XLP_UTILITY__
#define __XLP_UTILITY__

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <string.h>
#include <stdio.h>
#include <psputility.h>
#include <malloc.h>
#include <math.h>

#include "common.h"


/*
	Utility.OSK(inText, desc [,clearColor]) - Show the Sony OSK, and let the user enter a text.
 
		%arg string inText The text already set in the text box of the keyboard.
		%arg string desc The description of the text to enter, the description is shown under the text box.
		%arg color [clearColor] The color to clear the screen before showing the OSK, default: grey.
 
		%ret string The text that has been entered by the user.
 */

int Utility_OSK(lua_State *L);


/*
	Utility.message(message [,mode]) - Show a Sony official message.
 
		%arg string message The message to show.
		%arg number mode The kind of message: 0: simple message (Back), 1: Yes / No message, default: 0.
 
		%ret nothing.
 */

int Utility_message(lua_State *L);


/* 
	Utility.buttonPressed(mode) - Get the choice that has been made during the last Utility.message with Yes/No choice.
 
		%arg number mode The kind of return: 0: as a number, 1: as a string.
 
		%ret number/string If mode = 0 => 0 if yes has been chosen, 1 if No and 2 if Back has been chosen. If mode = 1: return "Yes", "No" or "Back".
 */

int Utility_buttonPressed(lua_State *L);


/*
	Utility.getNickname() - Get the nickname of the PSP.
 
		%arg nothing.
 
		%ret string The nickname of the PSP.
 */

int Utility_getNickname(lua_State *L);


/*
	Utility.getLanguage([retmode]) - Get the language of the PSP.
 
		%arg number [retmode] The mode you want to get the language, 1: as a string, 0: as a number, default: 0.
 
		%ret number/string The current language of the PSP. If retMode = 1: The name of the language. If retmode = 0: A number: 0 = japanese, 1 = English, 2 = French, 3 = Spanish, 4 = German, 5 = Italian, 6 = Dutch, 7 = Portuguese, 8 = Russian, 9 = Korean, 10 = Chinese Traditional, 11 = Chinese Simplified.
 */

int Utility_getLanguage(lua_State *L);



// XLP internal code //
int Utility_init(lua_State *L);

static const luaL_reg Utility_methods[] = { // Utility methods
	{"OSK", Utility_OSK},
	{"message", Utility_message},
	{"buttonPressed", Utility_buttonPressed},
	{"getNickname", Utility_getNickname},
	{"getLanguage", Utility_getLanguage},
	{0,0}
};

#endif

//EOF
