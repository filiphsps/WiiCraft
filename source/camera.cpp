/*									

	(c)Mojang AB And Filiph Sandström
									
									*/
#include <iostream>
#include <stdbool.h>
#include <stdint.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "camera.h"

using namespace std;

/*u8 camera::BlockLookingAt(int lAX,int lAY,int lAZ){
	
	/*for(int X;X  <= 32;X++){
		for(int Y;Y  <= 32;Y++){
			for(int Z;Z  <= 64;Z++){
				if(world[X][Z][Y] == true){
					if((world[++lAX][Y][Z] == true))worldLook[X][Y][Z] == 1;return worldLook[X][Y][Z];
					if(world[--lAX][Y][Z] == true)worldLook[X][Y][Z] == 2;return worldLook[X][Y][Z];
					if(world[X][++lAY][Z] == true)worldLook[X][Y][Z] == 3;return worldLook[X][Y][Z];
					if(world[X][--lAY][Z] == true)worldLook[X][Y][Z] == 4;return worldLook[X][Y][Z];
					if(world[X][Y][++lAZ] == true)worldLook[X][Y][Z] == 5;return worldLook[X][Y][Z];
					if(world[X][Y][--lAZ] == true)worldLook[X][Y][Z] == 6;return worldLook[X][Y][Z];
				}
			}
		}
	}*//*
	//Error:
	return worldLook[0][0][0];
}*/

void camera::calcCamera(int X, int Y, int Z){
X = Xpos;
Y = Ypos;
Z = Zpos;
}

void camera::updateWorld(int X,int Z,int Y,int ID){
	world[X][Z][Y] = ID;
}