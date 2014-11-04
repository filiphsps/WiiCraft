#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <ogc/lwp_watchdog.h>
#include "util.h"
#include "player.h"
#include "main.h"

using namespace std;

u32 LastRan = 2500;
u32 CurrentRun;

Player_s Player_l;
Velo_s Velo_l;
Gravity_s Gravity_l;

void* CalcPlayerPos(void* notUsed){
	while(true){
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
