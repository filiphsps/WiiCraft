#include <stdio.h>
#include <stdlib.h>
#include <asndlib.h>
#include <mp3player.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <grrlib.h>

#include "debug.h"

void Initialize(void){
	/* Debug */
	//TODO

	/* Initialise the Graphics & Video subsystem */
	GRRLIB_Init();
	GRRLIB_Settings.antialias = false;
	
	/* Controllers Initializations */
	WPAD_Init();
	WPAD_SetVRes(WPAD_CHAN_ALL, rmode->fbWidth, rmode->xfbHeight);
	WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);
}

void Deinitialize(void)
{
	GRRLIB_Exit ();
}