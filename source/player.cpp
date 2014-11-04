#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <ogc/lwp_watchdog.h>
#include <gccore.h>
#include "util.h"
#include "player.h"
#include "main.h"

#define STACK_SIZE 1024*64 // 64KB

using namespace std;

volatile u32 LastRan = 2500;
volatile u32 CurrentRun;
static volatile bool thread_running = true; // 
u8 stack[STACK_SIZE] ATTRIBUTE_ALIGN (32);
lwp_t tplayer;

Player_s Player_l;
Velo_s Velo_l;
Gravity_s Gravity_l;

void InitPlayerThread(void) {
	if (thread_running) return;
	thread_running = true;
	LWP_CreateThread( &tplayer, CalcPlayerPos, NULL, stack, STACK_SIZE, 64);
}

void StopPlayerThread(void) {
	if (!thread_running) return;
	thread_running = false;
	LWP_JoinThread(tplayer, NULL);
}

void* CalcPlayerPos(void* notUsed){
	while(thread_running){
		CurrentRun = GetTime();
		if(CurrentRun - LastRan > MSPERTICK){
			if(Velo_l.x != 0 || Velo_l.y != 0 || Velo_l.z != 0){
				/* X */
				if(Velo_l.x > 0){ //If not negative
					Player_l.x += Velo_l.x;
					Velo_l.x -= Gravity_l.x;
				} else{
					Player_l.x += Velo_l.x;
					Velo_l.x += Gravity_l.x;
				}
				
				/* Y */
				
				/* Z */
				
				LastRan = CurrentRun;
			}
		}
	}
	return NULL;
}

void InitPlayer(Player_s p, Gravity_s g){
	Player_l = p;
	Gravity_l = g;
}

Player_s GetPlayer(){
	return Player_l;
}
Velo_s GetVelocity(){
	return Velo_l;
}

void UpdatePlayer(Player_s p, Velo_s v){
	Velo_l.x = v.x;
	Velo_l.y = v.y;
	Velo_l.z = v.z;
}

u32 GetOldTime(){
	return LastRan;
}
u32 GetCurrentTime(){
	return CurrentRun;
}