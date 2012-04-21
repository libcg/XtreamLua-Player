/*
 *	XtreamLua Player - Final Version
 *	utility.c
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */


#include "utility.h"

#define maxLen 512
#define maxLine 20

void createOsk(SceUtilityOskData *data, unsigned short *input, unsigned short *desc)
{		
	unsigned short outtext[512] = { 0 };
	memset(data, 0, sizeof(SceUtilityOskData));
	data->language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT;
	data->lines = 1;
	data->unk_24 = 1;
	data->inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL;
	data->desc = desc;
	data->intext = input;
	data->outtextlength = maxLen;
	data->outtextlimit = 64;
	data->outtext = outtext;
	
	SceUtilityOskParams params;
	memset(&params, 0, sizeof(params));
	params.base.size = sizeof(params);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.base.buttonSwap);
	params.base.graphicsThread = 17;
	params.base.accessThread = 19;
	params.base.fontThread = 18;
	params.base.soundThread = 16;
	params.datacount = 1;
	params.data = data;
	
	
	sceUtilityOskInitStart(&params);
}


void charShort(const char *in, unsigned short *out)
{
	int i;
	
	for (i = 0; i < strlen(in); i++)
		out[i] = in[i];
	
	out[strlen(in)] = 0;
}

int Utility_OSK(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if (argc != 2 && argc != 3) return luaL_error(L, "Utility.OSK(inText, desc [,clearColor]): takes 2 or 3 arguments.");
	
	unsigned short* intext = memalign(16, sizeof(unsigned short)*(strlen(luaL_checkstring(L, 1))+1));
	charShort(luaL_checkstring(L, 1), intext);
	unsigned short* desc = memalign(16, sizeof(unsigned short)*(strlen(luaL_checkstring(L, 2))+1));
	charShort(luaL_checkstring(L, 2), desc);
	
	int i, done = 0;
	
	SceUtilityOskData data;
	createOsk(&data, intext, desc);
	
	g2dColor color = (argc == 3 ? luaL_checknumber(L, 3) : 0xFF808080);
	
	while(!done)
	{
		g2dClear(color);
		sceGuFinish();
		sceGuSync(0,0);
		
		switch(sceUtilityOskGetStatus())
		{
			case PSP_UTILITY_DIALOG_INIT:
				break;
				
			case PSP_UTILITY_DIALOG_VISIBLE:
				sceUtilityOskUpdate(1);
				break;
				
			case PSP_UTILITY_DIALOG_QUIT:
				sceUtilityOskShutdownStart();
				break;
				
			case PSP_UTILITY_DIALOG_FINISHED:
				break;
				
			case PSP_UTILITY_DIALOG_NONE:
				done = 1;
				
			default :
				break;
		}
		
		g2dFlip(G2D_VSYNC);
	}
	
	char *outtext = (char*) memalign(16, data.outtextlength*sizeof(char)+1);
	
	for (i = 0; i < data.outtextlength; ++i)
		outtext[i] = data.outtext[i];
	
	lua_pushfstring(L, "%s", outtext);
	
	free(desc);
	free(outtext);
	free(intext);
	
	return 1;
}

pspUtilityMsgDialogParams dialog;

void configureDialog(pspUtilityMsgDialogParams *dialog, size_t dialog_size)
{
    memset(dialog, 0, dialog_size);
	
    dialog->base.size = dialog_size;
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE,
								&dialog->base.language); // Prompt language
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN,
								&dialog->base.buttonSwap); // X/O button swap
	
    dialog->base.graphicsThread = 0x11;
    dialog->base.accessThread = 0x13;
    dialog->base.fontThread = 0x12;
    dialog->base.soundThread = 0x10;
}

void messageCreate(pspUtilityMsgDialogParams *dialog, const char* message, int mode, int opts)
{
	configureDialog(dialog, sizeof(pspUtilityMsgDialogParams));
    dialog->mode = mode;
	dialog->options = opts;
	
    strcpy(dialog->message, message);
    sceUtilityMsgDialogInitStart(dialog);
}

void showMessage(pspUtilityMsgDialogParams *dialog, g2dColor color)
{	
    sceUtilityMsgDialogInitStart(dialog);
	
	int done = 0;
	
    while (!done) 
	{
		g2dClear(color);
		
		g2dFlip(G2D_VSYNC);
		
		switch(sceUtilityMsgDialogGetStatus()) 
		{				
			case 2:
				sceUtilityMsgDialogUpdate(1);
				break;
				
			case 3:
				sceUtilityMsgDialogShutdownStart();
				break;
				
			case 0:
				done = 1;
				break;;
				
		}
	
		
    }
}

int Utility_message(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc < 1 || argc > 3) return luaL_error(L, "Utility.message(message [,mode ,backgroundColor]): takes 1, 2 or 3 arguments.");
	
	int yesNo = 0;
	
	if ((argc == 2) && (lua_type(L, 2) == LUA_TNUMBER))
		yesNo = luaL_checkint(L, 2);
	
	if (yesNo < 0 || yesNo > 1)
		return luaL_error(L, "Utility.message: wrong mode, must be 0 or 1.");
	
	int options = PSP_UTILITY_MSGDIALOG_OPTION_TEXT;
	
	g2dColor backColor = (argc == 3) ? luaL_checknumber(L, 3) : 0xFF554433;
	
	if(yesNo)
		options |= PSP_UTILITY_MSGDIALOG_OPTION_YESNO_BUTTONS;	
	
	messageCreate(&dialog, luaL_checkstring(L, 1), PSP_UTILITY_MSGDIALOG_MODE_TEXT, options);	
	
	const char *str = luaL_checkstring(L, 1);
    strcpy(dialog.message, str);
	
	showMessage(&dialog, backColor);
	
	
	return 0;
}

int Utility_buttonPressed(lua_State *L) //Utility.buttonPressed(mode): 0 = return 0,1 or 2. Something else or nothing: return Yes, No, Back
{	
	int mode = 1;
	
	if ((lua_gettop(L) > 0) && (lua_type(L, 1) == LUA_TNUMBER))
		mode = luaL_checknumber(L, 1);
	
	if (mode == 0)
	{
		int ret = 2; //Back
		
		if(dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
			ret = 0;//Yes
		else if(dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
			ret = 1; //No
		
		lua_pushnumber(L, ret);
	}
	
	else
	{
		
		if (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_YES)
			lua_pushstring(L, "Yes");
		else if (dialog.buttonPressed == PSP_UTILITY_MSGDIALOG_RESULT_NO)
			lua_pushstring(L, "No");
		else
			lua_pushstring(L, "Back");
	}
	
	return 1;
}

int Utility_getNickname(lua_State *L)
{	
	char nick[256];
	
	sceUtilityGetSystemParamString(PSP_SYSTEMPARAM_ID_STRING_NICKNAME, nick, 256);
	
	lua_pushstring(L, nick);
	
	return 1;
}


char *Utility_langs [12] = { // Every PSP Languages
	"Japanese",
	"English",
	"French",
	"Spanish",
	"German",
	"Italian",
	"Dutch",
	"Portuguese",
	"Russian",
	"Korean",
	"Chinese Traditional",
	"Chinese Simplified"
};

int Utility_getLanguage(lua_State *L)
{	
	int argc = lua_gettop(L);
	if (argc != 0 && argc != 1) return luaL_error(L, "Utility.getLanguage([retMode]): takes 0 or 1 argument.");
	
	int lang = 0;
	
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &lang);
	
	if (argc == 0)
	{
		lua_pushinteger(L, lang);
		return 1;
	}
	
	switch(luaL_checkint(L, 1))
	{
		case 0:
			lua_pushinteger(L, lang);
			break;
			
		case 1:
			lua_pushstring(L, Utility_langs[lang]);
			break;
			
		default:
			return luaL_error(L, "Utility.getLanguage([retMode]): retMode must be 0 (return as a number) or 1 (return as a string).");
	}
	
	return 1;
}

int Utility_init(lua_State *L)
{
	luaL_register(L, "Utility", Utility_methods);
	
	return 1;
}

// EOF
