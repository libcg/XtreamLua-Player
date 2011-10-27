/*
 *	XtreamLua Player - Final Version
 *	ctrl.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#ifndef __XLP_CTRL__
#define __XLP_CTRL__

#include "common.h"
#include <string.h>
#include <pspctrl.h>


/*
	Ctrl.read() - Read all buttons state.
 
		%arg nothing
		
		%ret ctrlData A variable with the buttons state.
 */

int Ctrl_read(lua_State *L);


/* 
	Ctrl.buttons(pad) - Get bit mask containing the control buttons, can be used like this: pad:buttons().
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret number The bit mask containing the control buttons.
 */

int Ctrl_buttons(lua_State *L);


/*
	Ctrl.cross(pad) - Get the state of the cross button, can be used like this: pad:cross()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the cross button is pressed, false if it isn't pressed.
 */

int Ctrl_cross(lua_State *L);


/*
	Ctrl.circle(pad) - Get the state of the circle button, can be used like this: pad:circle()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the circle button is pressed, false if it isn't pressed.
 */

int Ctrl_circle(lua_State *L);


/*
	Ctrl.triangle(pad) - Get the state of the triangle button, can be used like this: pad:triangle()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the triangle button is pressed, false if it isn't pressed.
 */

int Ctrl_triangle(lua_State *L);


/*
	Ctrl.square(pad) - Get the state of the square button, can be used like this: pad:square()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the square button is pressed, false if it isn't pressed.
 */

int Ctrl_square(lua_State *L);


/*
	Ctrl.down(pad) - Get the state of the down button, can be used like this: pad:down()

		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the down button is pressed, false if it isn't pressed.
 */

int Ctrl_down(lua_State *L);


/*
	Ctrl.right(pad) - Get the state of the right button, can be used like this: pad:right()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the right button is pressed, false if it isn't pressed.
 */

int Ctrl_right(lua_State *L);


/*
	Ctrl.up(pad) - Get the state of the up button, can be used like this: pad:up()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the up button is pressed, false if it isn't pressed.
 */

int Ctrl_up(lua_State *L);


/*
	Ctrl.left(pad) - Get the state of the left button, can be used like this: pad:left()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the left button is pressed, false if it isn't pressed.
 */

int Ctrl_left(lua_State *L);


/*
	Ctrl.l(pad) - Get the state of the left trigger, can be used like this: pad:l()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the left trigger is triggered, false if it isn't pressed.
 */

int Ctrl_l(lua_State *L);


/*
	Ctrl.r(pad) - Get the state of the right trigger, can be used like this: pad:r()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the right trigger is triggered, false if it isn't pressed.
 */

int Ctrl_r(lua_State *L);


/*
	Ctrl.start(pad) - Get the state of the start button, can be used like this: pad:start()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the start button is pressed, false if it isn't pressed.
 */

int Ctrl_start(lua_State *L);


/*
	Ctrl.select(pad) - Get the state of the select button, can be used like this: pad:select()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the select button is pressed, false if it isn't pressed.
 */

int Ctrl_select(lua_State *L);


/*
	Ctrl.hold(pad) - Get the state of the hold button, can be used like this: pad:hold()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the hold button is pressed, false if it isn't pressed.
 */

int Ctrl_hold(lua_State *L);


/*
	Ctrl.note(pad) - Get the state of the note button, can be used like this: pad:note()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the note button is pressed, false if it isn't pressed.
 */

int Ctrl_note(lua_State *L);


/*
	Ctrl.home(pad) - Get the state of the home button, can be used like this: pad:home()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the home button is pressed, false if it isn't pressed.
 */

int Ctrl_home(lua_State *L);


/*
	Ctrl.Lx(pad) - Get the value of the joystick's X-Axis, can be used like this: pad:Lx()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret number The value of the joystick's X-Axis, between 0 -> 128.
 */

int Ctrl_analogX(lua_State *L);


/*
	Ctrl.Ly(pad) - Get the value of the joystick's Y-Axis, can be used like this: pad:Ly()
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret number The value of the joystick's Y-Axis, between 0 -> 128.
 */

int Ctrl_analogY(lua_State *L);


/*
	tostring(pad) - Put a Ctrl value as string.
 
		%arg ctrlData pad A variable created with Ctrl.read().
 
		%ret string A string like this: "Ctrl: 16384" if cross is pressed.
 */

int Ctrl_tostring(lua_State *L);


/*
	pad1 == pad2 - Check if two Ctrl datas are equal or not.
 
		%arg ctrlData pad1 A variable created with Ctrl.read().
		%arg ctrlData pad2 A variable created with Ctrl.read().
 
		%ret boolean A boolean, true if the two pad datas are equal, false if they're not.
 */

int Ctrl_equal(lua_State *L);



// XLP internal code //
int Ctrl_init(lua_State *L);

static const luaL_reg Ctrl_methods[] = { //Ctrl methods
	{"read", Ctrl_read},
	{"buttons", Ctrl_buttons},
	
	{"cross", Ctrl_cross},
	{"circle", Ctrl_circle},
	{"square", Ctrl_square},
	{"triangle", Ctrl_triangle},
	
	{"down", Ctrl_down},
	{"right", Ctrl_right},
	{"left", Ctrl_left},
	{"up", Ctrl_up},
	
	{"l", Ctrl_l},
	{"r", Ctrl_r},
	
	{"start", Ctrl_start},
	{"select", Ctrl_select},
	{"note", Ctrl_note},
	{"home", Ctrl_home},
	
	{"hold", Ctrl_hold},
	
	{"Lx", Ctrl_analogX},
	{"Ly", Ctrl_analogY},
	{0, 0}
};

static const luaL_reg Ctrl_metamethods[] = { //Ctrl metamethods
	{"__tostring", Ctrl_tostring},
	{"__eq", Ctrl_equal},
	{0, 0}
};

#endif

//EOF
