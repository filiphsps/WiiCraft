#include <stdio.h>
#include <stdlib.h>
#include <asndlib.h>
#include <mp3player.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <grrlib.h>

#include "debug.h"

void Initialize(void){
	fatInitDefault();
	/* Debug */ 
	DebugStart(true, "sd://WiiCraft.log");
	Debug("-------------------[WiiCraft Debug Log]----------------------");
	Debug("DEBUG: Done!");
	
	Debug("/n");
	
	/* Controllers Initializations */
	Debug("PAD: Initializing... (1/2)");
	WPAD_Init();
	Debug("PAD: Initializing... (2/2)");
	PAD_Init();
	Debug("PAD: Configuring settings...");
	WPAD_SetVRes(WPAD_CHAN_ALL, rmode->fbWidth, rmode->xfbHeight);
	WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);
	Debug("PAD: Done!");
	
	Debug("/n");
	
	/* Initialise the Graphics & Video subsystem */
	Debug("GRRLIB: Initializing...");
	GRRLIB_Init();
	Debug("GRRLIB: Configuring settings...");
	GRRLIB_Settings.antialias = false;
	GRRLIB_SetAntiAliasing(false);
	Debug("GRRLIB: Done!");
}

void Deinitialize(void)
{
	Debug("GRRLIB: Stopping...");
	GRRLIB_Exit ();
	Debug("GRRLIB: Stopped!");
	
	Debug("/n");
	
	Debug("DEBUG: Stopping...");
	Debug("-------------------------------------------------------------");
	Debug("/n");
	Debug("/n");
	DebugStop();
}