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
volatile u32 pressed[3];
ir_t ir[3];
int connectedControllers = 3; //To do

void UpdateInput(){
	//ToDo: Only check more controllers if connected
	
	struct expansion_t data;
	WPAD_ScanPads();
	WPAD_Expansion(WPAD_CHAN_0, &data);
	pressed[0] = WPAD_ButtonsDown(0);
	WPAD_IR(0, &ir[0]);
	
	//Button Check
	if (pressed[0]) { //I could have used a switch here, but im too bad ass :P
		if (pressed[0] & WPAD_BUTTON_HOME) {
			Input_l->HOME[0] = true;
		} else if (pressed[0] & WPAD_BUTTON_B) {
			Input_l->B[0] = true;
		} else if (pressed[0] & WPAD_BUTTON_A) {
			Input_l->A[0] = true;
		} else if (pressed[0] & WPAD_BUTTON_DOWN) {
			Input_l->secondary_x[0] = 0;
		} else if (pressed[0] & WPAD_BUTTON_UP) {
			Input_l->secondary_x[0] = 255;
		} else if (pressed[0] & WPAD_BUTTON_RIGHT) {
			Input_l->secondary_y[0] = 255;
		} else if (pressed[0] & WPAD_BUTTON_LEFT) {
			Input_l->secondary_y[0] = 0;
		} else if (pressed[0] & WPAD_BUTTON_PLUS) {
			Input_l->PLUS[0] = true;
		} else if (pressed[0] & WPAD_BUTTON_MINUS) {
			Input_l->MINUS[0] = true;
		} else if (pressed[0] & WPAD_BUTTON_1) {
			Input_l->_1[0] = true;
		} else if (pressed[0] & WPAD_BUTTON_2) {
			Input_l->_2[0] = true;
		} else if (pressed[0] & WPAD_NUNCHUK_BUTTON_Z) {
			Input_l->Z[0] = true;
		} else if (pressed[0] & WPAD_NUNCHUK_BUTTON_C) {
			Input_l->C[0] = true;
		} else{
			Input_l->secondary_x[0] = 128;
			Input_l->secondary_y[0] = 128;
		}
	}
	else{
		RestAllButtons();
	}
	//Axis Check
	Input_l->main_x[0] = ir[0].x;
	Input_l->main_y[0] = ir[0].y;
	if (data.type == WPAD_EXP_NUNCHUK) {
		Input_l->secondary_x[0] = data.nunchuk.js.pos.y;
		Input_l->secondary_y[0] = data.nunchuk.js.pos.x;
		Input_l->isNunchuck[0] = true;
	}
	else{
		Input_l->isNunchuck[0] = false;
	}
	/*else if(TODO){
		if (PAD_StickY(1) > 18) {
			Input_l->secondary_y[0]--;
		}
		if (PAD_StickY(1) < -18) {
			Input_l->secondary_x[0]++;
		}
		if (PAD_StickX(1) > 18) {
			Input_l->secondary_x[0]++;
		}
		if (PAD_StickX(1) < -18) {
			Input_l->secondary_x[0]--;
		}
	}*/
}

void RestAllButtons(){
	for(int x = 0; x < connectedControllers; x++){
		Input_l->A[x] = false;
		Input_l->B[x] = false;
		Input_l->PLUS[x] = false;
		Input_l->MINUS[x] = false;
		Input_l->HOME[x] = false;
		Input_l->C[x] = false;
		Input_l->Z[x] = false;
		Input_l->ZL[x] = false;
		Input_l->ZR[x] = false;
		Input_l->secondary_x[x] = 128;
		Input_l->secondary_y[x] = 128;
	}
}

void InitInput(Input_s* input){
	Input_l = input;
}