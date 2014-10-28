#include <stdio.h>
#include <stdlib.h>
#include <asndlib.h>
#include <mp3player.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <grrlib.h>

#include "debug.h"

void Initialize(void){
	//Debug:
	#ifdef USBGECKO
	GRRLIB_GeckoInit();
	DebugStart(true, "sd://segui.log");
	Debug("-------------------[Wiicraft Debug]----------------------");
	gprintf("Done With init()\n");
	#endif


	// Initialise the Graphics & Video subsystem
	GRRLIB_Init();
	//VIDEO_Init();
	// button initialization
	WPAD_Init();
	WPAD_SetVRes(0, 640, 480);
	WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);
	// Initialse the sound system
	ASND_Init();
	MP3Player_Init();
	//HomeMenu_Init(int 640, int 480, void* framebuffer0, void* framebuffer1, u8 framebufferIndex);
	//HomeMenu_SetGFX(HM_GFX_GRRLIB);
	//HomeMenu_SetSND(HM_SND_ASND);

}

void Deinitialize(void)
	{
	GRRLIB_Exit ();
	#ifdef USBGECKO
	Debug("GRRLIB_Exit Passed");
	#endif

	ASND_End();
	#ifdef USBGECKO
	Debug("ASND_End Passed");
	#endif

	void MP3Player_Stop();
	#ifdef USBGECKO
	Debug("MP3Player_Stop Passed");
	#endif

	#ifdef USBGECKO
	DebugStop();
	gprintf("DebugStop passed\n");
	#endif
	}