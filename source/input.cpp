#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <ogc/lwp_watchdog.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "input.h"
#include "util.h"

using namespace std;

Input_s* Input_l;
u32 pressed[3];
ir_t ir[3];

void UpdateInput(){
	//ToDo
	struct expansion_t data;
	WPAD_ScanPads();
	WPAD_Expansion(WPAD_CHAN_0, &data);
	pressed[0] = WPAD_ButtonsDown(0);
	WPAD_IR(0, &ir[0]);
	
	//Button Check
	
	//Axis Check
	Input_l->main_x = ir[0].x;
	Input_l->main_y = ir[0].y;
	if (data.type == WPAD_EXP_NUNCHUK) {
		Input_l->secondary_x = data.nunchuk.js.pos.x;
		Input_l->secondary_y = data.nunchuk.js.pos.y;
	}
	else{
	
	}
}

void InitInput(Input_s* input){
	Input_l = input;
}