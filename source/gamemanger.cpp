#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <ogc/lwp_watchdog.h>
#include <gccore.h>
#include "util.h"
#include "gamemanger.h"
#include "main.h"
#include "player.h"

using namespace std;

static volatile bool thread_running = false; 
u8 stack[STACK_SIZE] ATTRIBUTE_ALIGN (32);
lwp_t gm_t;

int TestingGM = 0;
volatile u32 LastRan = 2500;
volatile u32 CurrentRun;

void InitGMThread(void) {
	if (thread_running) return;
	thread_running = true;
	LWP_CreateThread( &gm_t, GameManager, NULL, stack, STACK_SIZE, 64);
}

void StopGMThread(void) {
	if (!thread_running) return;
	thread_running = false;
	LWP_JoinThread(gm_t, NULL);
}

void* GameManager(void*){
	while(thread_running){
		//TODO
		CurrentRun = GetTime();
		if(CurrentRun - LastRan > MSPERTICK){
			CalcPlayerPos(); //Calculate player(s) position
			LastRan = CurrentRun;
		}
	}
	return NULL;
}