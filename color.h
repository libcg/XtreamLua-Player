/*
 *	XtreamLua Player - Final Version
 *	color.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#ifndef __XLP_COLOR__
#define __XLP_COLOR__

#include "common.h"


/*
	Color.create(r, g, b [,a]) - Create a color, used to print a text, or with the gLib2D.
 
		%arg number r The red mask intensity, between 0 -> 255.
		%arg number g The green mask intensity, between 0 -> 255.
		%arg number b The blue mask intensity, between 0 -> 255.
		%arg number [a] The alpha-value of the color, between 0 -> 255, default: 255.
 
		%ret color The created color.
 */

int Color_create(lua_State *L);


/*
	Color.getR(color) - Get the red mask intensity from a color.
 
		%arg color color The color to get the red mask intensity.
 
		%ret number The red mask intensity.
 */

int Color_getR(lua_State *L);


/*
 Color.getG(color) - Get the green mask intensity from a color.
 
		%arg color color The color to get the green mask intensity.
 
		%ret number The green mask intensity.
 */

int Color_getG(lua_State *L);


/*
	Color.getB(color) - Get the blue mask intensity from a color.
 
		%arg color color The color to get the blue mask intensity.
 
		%ret number The blue mask intensity.
 */

int Color_getB(lua_State *L);


/*
	Color.getA(color) - Get the alpha value from a color.
 
		%arg color color The color to get the alpha value.
 
		%ret number The alpha value.
 */

int Color_getA(lua_State *L);


/*
	Color.getColor(color, [mask]) - Get the red, green and blue masks intensity and the alpha value of a color.
 
		%arg color color The color to get the intensities.
		%arg string [mask] The mask to get the intensity, "R", "G", "B" or "A", default: all masks
 
		%ret number The asked value(s), if mask is as default (not passed), return 4 values. e.g: local r,g,b,a = Color.getColor(myColor).
 */

int Color_getColor(lua_State *L);


/*
	tostring(color) - Get the colors masks and put them in a string.
 
		%arg color color The color that you want to get the components.
 
		%ret A string like this: "Color: R=255, G=255, B=255, A=255".
 */

//int Color_tostring(lua_State *L);


// XLP internal code //
int Color_init(lua_State *L);

static const luaL_reg Color_methods[] = { // Color methods
	{"create", Color_create},
	{"getR", Color_getR},
	{"getG", Color_getG},
	{"getB", Color_getB},
	{"getA", Color_getA},
	{"getColor", Color_getColor},
	{0,0}
};

/*static const luaL_reg Color_metamethods[] = { // Color metamethods
	{"__tostring", Color_tostring},
	{0,0}
};*/

#endif

//EOF
