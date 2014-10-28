/*									

	(c)Mojang AB And Filiph Sandström
									
									*/
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <stdbool.h>
#include <stdint.h>
#include <gccore.h>
#include <wiiuse/wpad.h> 

using namespace std;

class camera{
	private:
	u8 world[32][32][64];
	u8 worldLook[32][32][64];
	int Xpos;
	int Ypos;
	int Zpos;
	
	public:
	//u8 BlockLookingAt(int lAX,int lAY,int lAZ);
	void calcCamera(int X,int Y,int Z);
	void updateWorld(int X,int Z,int Y,int ID);
	
};

#endif