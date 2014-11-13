#include <stdio.h>
#include <stdlib.h>
#include <asndlib.h>
#include <mp3player.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <grrlib.h>
#include <fat.h>

#include "debug.h"

void Initialize(void){
	if (!fatInitDefault()) {
		//error
		printf("Error: Do you even SD brah?");
		//exit(0);
	}
	/* Debug */ 
	DebugStart(true, "sd://WiiCraft.log");
	Debug("-------------------[WiiCraft Debug Log]----------------------");
	Debug("DEBUG: Done!");
	
	Debug("/n");
	
	/* Controllers Initializations */
	Debug("PAD: Initializing... (1/3)");
	//WUPC_Init(); //Wii U Pro Controller
	Debug("PAD: Initializing... (2/3)");
	WPAD_Init();
	Debug("PAD: Initializing... (3/3)");
	PAD_Init();
	Debug("PAD: Configuring settings...");
	WPAD_SetVRes(0, 640, 480);
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR); 
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
	
	Debug("PAD: Stopping (1/2)");
	//WUPC_Shutdown(); //Wii U Pro Controller
	Debug("PAD: Stopping (1/2)");
	WPAD_Shutdown();
	
	Debug("/n");
	
	Debug("DEBUG: Stopping...");
	Debug("-------------------------------------------------------------");
	Debug("/n");
	Debug("/n");
	DebugStop();
}
