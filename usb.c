/*
 *	XtreamLua Player - Final Version
 *	usb.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#include "usb.h"

/* Load module, code taken from pspsdk samples ;)*/
int LoadStartModule(char *path)
{
    u32 loadResult;
    u32 startResult;
    int status;
	
    loadResult = sceKernelLoadModule(path, 0, NULL);
    if (loadResult & 0x80000000)
		return -1;
    else
		startResult = sceKernelStartModule(loadResult, 0, NULL, &status, NULL);
	
    if (loadResult != startResult)
		return -2;
	
    return 0;
}

void cleanUSBDrivers()
{
    if (usbState &PSP_USB_ACTIVATED)
		usbState = sceUsbDeactivate(0);
	
    usbState = sceUsbStop(PSP_USBSTOR_DRIVERNAME, 0, 0);
	
    usbState = sceUsbStop(PSP_USBBUS_DRIVERNAME, 0, 0);
}

int loadUSB()
{
	if (usbActivate) return 1;
	
	if (!usbModules)
	{
		LoadStartModule("flash0:/kd/semawm.prx");
		LoadStartModule("flash0:/kd/usbstor.prx");
		LoadStartModule("flash0:/kd/usbstormgr.prx");
		LoadStartModule("flash0:/kd/usbstorms.prx");
		LoadStartModule("flash0:/kd/usbstorboot.prx");
		
		int usb_init;
		
		usb_init = sceUsbStart(PSP_USBBUS_DRIVERNAME, 0, 0); 
		if (usb_init != 0) 
			printf("Error starting USB Bus driver (0x%08X)\n", usb_init); 
		
		usb_init = sceUsbStart(PSP_USBSTOR_DRIVERNAME, 0, 0); 
		if (usb_init != 0) 
			printf("Error starting USB Mass Storage driver (0x%08X)\n", usb_init); 
		
		usb_init = sceUsbstorBootSetCapacity(0x800000); 
		if (usb_init != 0)
			printf("Error setting capacity with USB Mass Storage driver (0x%08X)\n", usb_init); 
		
		usbModules = 1;
	}
	
	
	return 1;
}

int unloadUSB()
{
	sceUsbStop(PSP_USBSTOR_DRIVERNAME, 0, 0);
	sceUsbStop(PSP_USBBUS_DRIVERNAME, 0, 0);
	
	return 1;
}


int USB_activate(lua_State *L)
{
	loadUSB();
	
	usbState = sceUsbActivate(0x1c8);
	
	if (usbState)
		return luaL_error(L, "Failed to activate USB.");
	
	usbActivate = 1;
	
	return 1;
}

int USB_deActivate(lua_State *L)
{
	if (!usbActivate) return 1;
	
	usbState = sceUsbDeactivate(0x1c8);
	
	unloadUSB();
	
	if (usbState)
		return luaL_error(L, "Failed to deactivate USB.");
	
	usbActivate = 0;
	
	return 1;
}

int USB_isActivated(lua_State *L)
{
	lua_pushboolean(L, usbActivate == 1 ? true : false);
	
	return 1;
}

int USB_init(lua_State *L)
{
	usbState = 0;
	usbActivate = 0;
	usbModules = 0;
	
	luaL_register(L, "USB", USB_methods);
	
	return 1;
}

