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


#ifndef __XLP_INTRA__
#define __XLP_INTRA__

#include "common.h"
#include <libtext.h>


/*
	intraFont.load(fontpath) - Load an intrafont file, format: .pgf (fonts can be found at flash0:/font/)
 
		%arg string fontpath The path of the font to load.
 
		%ret font The loaded font.
 */

int intraFont_load(lua_State *L);


/*
	intraFont.print(font, x, y, text [,size, color, shadowColor, angle, alignMode]) - Print a text with a specified font, can be used like this: font:print(x, y, text [,size, color, shadowColor, angle, alignMode])
 
		%arg font font The specified font to print the text.
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg number size The size of the text, default: 1.0
		%arg color color The color to print the text, default: white.
		%arg color shadowColor The shadow's color of the text, default: none.
		%arg number angle The rotation's angle of the text, in degrees, default: 0.
		%arg mode alignMode The mode of alignement, either intraFont.LEFT, intraFont.CENTER or intraFont.RIGHT, default: intraFont.LEFT.
 
		%ret number The X-Coordinate of the last printed character.
 */

int intraFont_print(lua_State *L);


/*
	intraFont.printBordered(font, x, y, text [,size, color, borderColor, angle, alignMode]) - Print a text with a border of 1 pixel, can be used like this: font:printBordered(x, y, text [,size, color, borderColor, angle, alignMode])
 
		%arg font font The specified font to print the text.
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg number size The size of the text, default: 1.0
		%arg color color The color to print the text, default: white.
		%arg color borderColor The color of the border, default: black.
		%arg number angle The rotation's angle of the text, in degrees, default: 0.
		%arg mode alignMode The mode of alignement, either intraFont.LEFT, intraFont.CENTER or intraFont.RIGHT, default: intraFont.LEFT.
 
		%ret number The X-Coordinate of the last printed character.
 */

int intraFont_PrintBordered(lua_State *L);


/*
	intraFont.printUnderlined(font, x, y, text [,size, color, lineColor, alignMode]) - Print an underlined text, can be used like this: font:printUnderlined(x, y, text [,size, color, lineColor, alignMode])
 
		%arg font font The specified font to print the text.
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg number size The size of the text, default: 1.0
		%arg color color The color to print the text, default: white.
 		%arg color lineColor The color of the line, default: black.
		%arg number angle The rotation's angle of the text, in degrees, default: 0.
		%arg mode alignMode The mode of alignement, either intraFont.LEFT, intraFont.CENTER or intraFont.RIGHT, default: intraFont.LEFT.
 
		%ret number The X-Coordinate of the last printed character.
 */

int intraFont_PrintUnderlined(lua_State *L);


/*
	intraFont.printReversed(font, x, y, text [,size, color, shadowColor, angle, alignMode]) - Print a text reversed (test -> tset), can be used like this: font:printBordered(x, y, text [,size, color, shadowColor, angle, alignMode])
 
		%arg font font The specified font to print the text.
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg number size The size of the text, default: 1.0
		%arg color color The color to print the text, default: white.
		%arg color shadowColor The shadow's color of the text, default: none.
		%arg number angle The rotation's angle of the text, in degrees, default: 0.
		%arg mode alignMode The mode of alignement, either intraFont.LEFT, intraFont.CENTER or intraFont.RIGHT, default: intraFont.LEFT.
 
		%ret number The X-Coordinate of the last printed character.
 */

int intraFont_PrintReversed(lua_State *L);


/*
	intraFont.printAlphaGradient(font, x, y, text [,size, color, gradientColor, gradientMode, angle, alignMode]) - Print a text with an alpha gradient, can be used like this: font:printAlphaGradient(x, y, text [,size, color, gradientColor, gradientMode, angle, alignMode])
 
		%arg font font The specified font to print the text.
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg number size The size of the text, default: 1.0
		%arg color color The color to print the text, default: white.
		%arg color gradientColor The color of the gradient, default: black.
		%arg mode gradientMode Set where the gradient goes, either intraFont.G_UP, intraFont.G_RIGHT, intraFont.G_DOWN, intraFont.G_LEFT, intraFont.G_UP_LEFT, intraFont.G_UP_RIGHT, intraFont.G_DOWN_LEFT or intraFont.G_DOWN_RIGHT, default: intraFont.G_UP_LEFT.
		%arg number angle The rotation's angle of the text, in degrees, default: 0.
		%arg mode alignMode The mode of alignement, either intraFont.LEFT, intraFont.CENTER or intraFont.RIGHT, default: intraFont.LEFT.
 
		%ret number The X-Coordinate of the last printed character.
 */

int intraFont_PrintAlphaGradient(lua_State *L);


/*
	intraFont.printDroppedShadow(font, x, y, text [,size, color, shadowColor, intensity, angle, alignMode]) - Print a text with a dropped shadow, can be used like this: font:printDroppedShadow(x, y, text [,size, color, shadowColor, intensity, angle, alignMode])
 
		%arg font font The specified font to print the text.
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg number size The size of the text, default: 1.0
		%arg color color The color to print the text, default: white.
		%arg color shadowColor The color of the shadow, default: black.
		%arg number intensity The intensity of the shadow, between 0 -> 255, default: 30.
		%arg number angle The rotation's angle of the text, in degrees, default: 0.
		%arg mode alignMode The mode of alignement, either intraFont.LEFT, intraFont.CENTER or intraFont.RIGHT, default: intraFont.LEFT.
 
		%ret number The X-Coordinate of the last printed character.
 */

int intraFont_PrintShadowed(lua_State *L);


/*
	intraFont.printBackgrounded(font, x, y, text [,size, color, backgroundColor, alignMode]) - Print a text with an unicolored background, can be used like this: font:printBackgrounded(x, y, text [,size, color, backgroundColor, alignMode])

		%arg font font The specified font to print the text.
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg number size The size of the text, default: 1.0
		%arg color color The color to print the text, default: white.
		%arg color backgroundColor The background's color, default: black.
		%arg mode alignMode The mode of alignement, either intraFont.LEFT, intraFont.CENTER or intraFont.RIGHT, default: intraFont.LEFT.
 
		%ret number The X-Coordinate of the last printed character.
 */

int intraFont_PrintBackgrounded(lua_State *L);


/*
	intraFont.printStriked(font, x, y, text [,size, color, lineColor, alignMode]) - Print a striked text, can be used like this: font:printStriked(x, y, text [,size, color, lineColor, alignMode])
 
		%arg font font The specified font to print the text.
		%arg number x The X-Coordinate of the text.
		%arg number y The Y-Coordinate of the text.
		%arg string text The text to print.
		%arg number size The size of the text, default: 1.0
		%arg color color The color to print the text, default: white.
		%arg color lineColor The color of the line, default: black.
		%arg number angle The rotation's angle of the text, in degrees, default: 0.
		%arg mode alignMode The mode of alignement, either intraFont.LEFT, intraFont.CENTER or intraFont.RIGHT, default: intraFont.LEFT.
 
		%ret number The X-Coordinate of the last printed character.
 */

int intraFont_PrintStriked(lua_State *L);


/*
	intraFont.undload(font) - Unload a font, can be used like this: font:unload().
 
		%arg font font The font to unload.
 
		%ret number The X-Coordinate of the last printed character.
 */

int intraFont_free(lua_State *L);


/*
	tostring(font) - Get the pointer of a font, in a string.
 
		%arg font font The font which you want to get the pointer.

		%ret string A string on this sample: "intraFont: 0xXXXXXXXX".
 */

int intraFont_tostring(lua_State *L);



// XLP internal code //
int intraFont_init(lua_State *L);

static const luaL_reg intraFont_methods[] = { // intraFont methods
	{"load", intraFont_load},
	{"print", intraFont_print},
	{"printBordered", intraFont_PrintBordered},
	{"printUnderlined", intraFont_PrintUnderlined},
	{"printReversed", intraFont_PrintReversed},
	{"printAlphaGradient", intraFont_PrintAlphaGradient},
	{"printDroppedShadow", intraFont_PrintShadowed},
	{"printBackgrounded", intraFont_PrintBackgrounded},
	{"printStriked", intraFont_PrintStriked},
	{"unload", intraFont_free},
	{0,0}
};

static const luaL_reg intraFont_metamethods[] = { // intraFont metamethods
	{"__tostring", intraFont_tostring},
	{"__gc", intraFont_free},
	{0,0}
};

#endif

// EOF
