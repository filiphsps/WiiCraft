#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <ogc/lwp_watchdog.h>
#include <gccore.h>
#include <grrlib.h>
#include "util.h"
#include "gui.h"
#include "gamemanger.h"
#include "main.h"

using namespace std;
//GRRLIB_texImg *texBlock;
GRRLIB_texImg **textures;

void RenderInventory(int blockId){
	//ToDo
}
void InitGUI(GRRLIB_texImg *text[]){
	textures = text;
}