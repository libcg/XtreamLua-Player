// XtreamLua Player by FlavR

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luaconf.h>

#include <psptypes.h>
#include <malloc.h>
#include <psputils.h>
#include <png.h>
#include <pspgu.h>

#include "common.h"
#include "aalib.h"
#include "color.h"
#include "g2d.h"
#include "intra.h"
#include "ctrl.h"
#include "power.h"
#include "time.h"
#include "timer.h"
#include "savedata.h"
#include "sceIo.h"
#include "utility.h"
#include "usb.h"
#include "xtream.h"

PSP_MODULE_INFO("XLP", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(20480);


/* Exit callback */
int exit_callback(void)
{	
	sceKernelExitGame();
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", (void *) exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();
	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}


int main(int argc, char** argv)
{
	pspDebugScreenInit();
	pspDebugScreenEnableBackColor(0);
	
	SetupCallbacks();
	
	char* scriptFilename = "script.lua";
	
	lua_State *L;
	L = lua_open();
	luaL_openlibs(L);
	
	Aalib_init(L);
	Color_init(L);
	g2D_init(L);
	intraFont_init(L);
	Ctrl_init(L);
	Power_init(L);
	Time_init(L);
	Timer_init(L);
	Savedata_init(L);
	sceIo_init(L);
	Utility_init(L);
	USB_init(L);
	Xtream_init(L);
	
	
	SceCtrlData keys, oldkeys;
	int status = 0, i;
	
	while (1)
	{
	status = luaL_loadfile(L, scriptFilename);
		
	if (status == 0) 
		status = lua_pcall(L, 0, LUA_MULTRET, 0);
	

		if (status != 0) //If an error has occured
		{
		sceCtrlReadBufferPositive(&oldkeys, 1);
		
		pspDebugScreenInit();
		pspDebugScreenEnableBackColor(1);
		
			while (1)
			{			
				sceCtrlReadBufferPositive(&keys, 1);
			
				pspDebugScreenSetXY(0,0);
				printf("Lua Error:\n%s\n", lua_tostring(L, -1));
				printf("Press Start to reset.\n");
				
				if ((keys.Buttons &PSP_CTRL_START) && !(oldkeys.Buttons &PSP_CTRL_START))
					break;
				
				oldkeys = keys;
				
				for (i = 0; i < 10; i++)
					sceDisplayWaitVblankStart();
			}
			
		pspDebugScreenInit();
		pspDebugScreenEnableBackColor(0);
		
		lua_pop(L, 1);
		}
	}
		
	lua_close(L);

	intraFontShutdown();
	g2dTerm();
	cleanUSBDrivers();

	sceKernelExitGame();

	return 0;
}

// EOF
