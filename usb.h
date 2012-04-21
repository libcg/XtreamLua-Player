/*
 *	XtreamLua Player - Final Version
 *	usb.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#ifndef __XLP_USB__
#define __XLP_USB__

#include "common.h"

#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspusb.h>
#include <pspusbstor.h>


/*
	USB.activate() - Activate the USB connection.
 
		%arg nothing.
 
		%ret nothing.
 */

int USB_activate(lua_State *L);


/*
	USB.deactivate() - Deactivate the USB connection.
 
		%arg nothing.
 
		%ret nothing.
 */

int USB_deActivate(lua_State *L);


/*
	USB.isActivated() - Check if the USB is activated or not.
 
		%arg nothing.
 
		%ret boolean true if the USB is activated, false if it isn't.
 */

int USB_isActivated(lua_State *L);



// XLP internal code //
int USB_init(lua_State *L);

void cleanUSBDrivers();
int loadUSB();
int unloadUSB();

static const luaL_reg USB_methods[] = {
	{"activate", USB_activate},
	{"deactivate", USB_deActivate},
	
	{"isActivated", USB_isActivated},
	{0,0}
};

#endif

// EOF
