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
#include "gamemanger.h"
#include "main.h"

using namespace std;

Player_s* Player_l;
Gravity_s* Gravity_l;
Velo_s* Velo_l;

void CalcPlayerPos(){
	if(Velo_l->x != 0 || Velo_l->y != 0 || Velo_l->z != 0){
		/* X */
		if(Velo_l->x > 0){ //If not negative
			Player_l->x += Velo_l->x;
			Velo_l->x -= Gravity_l->x;
		} else{
			Player_l->x += Velo_l->x;
			Velo_l->x += Gravity_l->x;
		}
		
		/* Y */
		
		/* Z */
		
	}
}

void InitPlayer(Player_s* p, Gravity_s* g){
	Player_l = p;
	Gravity_l = g;
}

u32 GetOldTime(){
	return LastRan;
}
u32 GetCurrentTime(){
	return CurrentRun;
}