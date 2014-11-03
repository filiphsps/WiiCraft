/*

	(c)2012-2014 Filiph Sandström & filfat Studio's

*/

//Standard libray:
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <ogc/lwp_watchdog.h>
#include <wiiuse/wpad.h>

//Network:
#include <network.h>

//GRRLIB:
#include <grrlib.h>

//Classes:
#include "drawcube.h"
#include "main.h"
#include "debug.h"
#include "camera.h"
#include "init.h"
#include "chunk.h"

//Fonts:
#include "BMfont5_png.h"

//Images:
#include "pointer1_png.h"
#include "Pointer_png.h"
#include "logo_png.h"

//Blocks:
#include "Stone_png.h"
#include "GrassUp_png.h"
#include "Dirt_png.h"
#include "Cobblestone_png.h"
#include "Wood_png.h"
#include "WoodBirch_png.h"
#include "Bedrock_png.h"
#include "LogUp_png.h"

//Wiilight
#define HW_GPIO             0xCD0000C0;
#define DISC_SLOT_LED       0x20

extern "C" {
	extern void __exception_setreload(int t);
}

using namespace std;

//Variables
const int sizex = 128;
const int sizey = 128;
const int sizez = 64;
const int SIZEZ = 64;
int BlockInHand = 1;
int BlockInHandFix = 0;
int lookingAtX = 36;
int lookingAtY = 36;
int lookingAtZ = 32;
int upx = 0;
int upy = 1;
int upz = 0;
int lAX;
int lAY;
int lAZ;
bool save_used = false;
bool debug = true;
bool running = true;
u8 FPS = 0;
//Textures
GRRLIB_texImg *tex_pointer1;
GRRLIB_texImg *texBlockPointer;
GRRLIB_texImg *tex_BMfont5;
GRRLIB_texImg *tex_logo;
GRRLIB_texImg *texStone;
GRRLIB_texImg *texGrassUp;
GRRLIB_texImg *texDirt;
GRRLIB_texImg *texCobblestone;
GRRLIB_texImg *texWoodenPlanks;
GRRLIB_texImg *texBedrock;
//WiiMote
ir_t ir1;
u32 pressedP1;
struct expansion_t data; //Nunchuks
//WiiLight
lwp_t light_thread = 0;
void *light_loop (void *arg);
vu32 *light_reg = (u32*) HW_GPIO;
bool light_on = false;
u8 light_level = 0;
struct timespec light_timeon = { 0 };
struct timespec light_timeoff = { 0 };

/*
	Functions
*/
static u8 CalculateFrameRate();
void WIILIGHT_TurnOn();
void WIILIGHT_TurnOff();
void WIILIGHT_SetLevel(int level);

int xx;
int yy;
int zz;
int CPx = 15;
int CPy = 0;
int CPz = 0;
float CameraRotY = 0;

struct CurrentChunkTranslatestru{
	int x;
	int y;
	int z;
};

u8 CurrentChunk[sizex][sizey][sizez];
u8 CurrentChunkLook[sizex][sizey][sizez];

static mutex_t mutex;
static mutex_t chunkH;

/*
	void* ChunkHandler()
	Makes sure the game uses the current chunk(s)
*/
void* ChunkHandler(void* notUsed){
	//TODO: Change the variable "CurrentChunk" to ONLY include the vissible chunks
	
	return NULL;
}


/*
	void* render()
	used to render the game
*/
void* render(void* notUsed){
	//Draw Cube
	drawcube cube(lookingAtX, lookingAtZ, lookingAtY);
	xx = lookingAtX;
	yy = lookingAtY;
	zz = lookingAtZ;
	while (running){
		lAX = lookingAtX;
		lAY = lookingAtY;
		lAZ = lookingAtZ;
		
		GRRLIB_Camera3dSettings(lAX + 8,lAY,lAZ + 3, 0,0,1, CPx >= 15 ? 15 : CPx + 5,lAY/*TODO!!*/,lAZ);
		
		GRRLIB_2dMode();
		GRRLIB_DrawImg(ir1.sx - 48, ir1.sy - 45, tex_pointer1, 0, 1, 1, 0xffffffff);
		if(save_used){
			for(int x = 0;x < sizex; x++){
				for(int y = 0;y < sizey; y++){
					for(int z = 0;z < sizez; z++){
						switch((CurrentChunk[x][y][z])){
							case 0:
							break;
							case 1:
								/* Stone: */
								cube.drawcubeBlock(x,z,y, texStone);
								break;
							case 2:
								/* Grass: */
								cube.drawcubeBlock(x,z,y, texGrassUp);
								break;
							case 3:
								/* Dirt */
								cube.drawcubeBlock(x,z,y, texDirt);
								break;
							case 4:
								/* Cobblestone: */
								cube.drawcubeBlock(x,z,y, texCobblestone);
								break;
							case 5:
								/* Wooden Planks: */
								cube.drawcubeBlock(x,z,y, texWoodenPlanks);
								break;
							case 6:
								/* Empty */
								break;
							case 7:
								/* Bedrock: */
								cube.drawcubeBlock(x,z,y, texBedrock);
								break;
							case 12:
								break;
							default:
								break;
						}
					}
				}
			}
		}
		cube.drawcubeBlock(lookingAtX,lookingAtZ,lookingAtY, texBlockPointer);
		//Might aswell draw the text in this thread
		GRRLIB_2dMode();
		GRRLIB_Printf(17, 18, tex_BMfont5, WHITE, 1, "WiiCraft Dev Build");
		if(!debug){
			GRRLIB_Printf(240, 18, tex_BMfont5, WHITE, 1, "Press 1+2 for debug information.");
		}
		else {
			GRRLIB_Printf(17, 39, tex_BMfont5, WHITE, 1, "FPS: %d", FPS);
			GRRLIB_Printf(17, 57, tex_BMfont5, WHITE, 1, "X: %d", static_cast<int>(lookingAtX));
			GRRLIB_Printf(17, 76, tex_BMfont5, WHITE, 1, "Y: %d", static_cast<int>(lookingAtY));
			GRRLIB_Printf(17, 95, tex_BMfont5, WHITE, 1, "Z: %d", static_cast<int>(lookingAtZ));
			GRRLIB_Printf(17, 210, tex_BMfont5, WHITE, 1, "CRY: %f", CameraRotY);
			FPS = CalculateFrameRate(); //Performance decrease when used!
		}
		GRRLIB_Printf(17, 114, tex_BMfont5, WHITE, 1, "Current block in hand: %d:%d", static_cast<int>(BlockInHand),BlockInHandFix);
		GRRLIB_Render();
		VIDEO_WaitVSync();
	}
	return NULL;
}

/*
	int main()
	The main function
*/

//---------------------------------------------------------------------------------
int main()
//---------------------------------------------------------------------------------
{
	// In the event of a code dump, the app will exit after 10 seconds (unless the user presses POWER)
	__exception_setreload(10);
	
	/*
		Initialize
	*/
	WIILIGHT_SetLevel(255);
	WIILIGHT_TurnOn();
	
	Initialize();

	WIILIGHT_TurnOff();

	WPAD_IR(WPAD_CHAN_1, &ir1);
	
	/*
		GRRLIB Related
	*/
	tex_pointer1 = GRRLIB_LoadTexture(pointer1_png);
	texBlockPointer = GRRLIB_LoadTexture(Pointer_png);
	tex_BMfont5 = GRRLIB_LoadTexture(BMfont5_png);
	tex_logo = GRRLIB_LoadTexture(logo_png);
	texStone = GRRLIB_LoadTexture(Stone_png);
	texGrassUp = GRRLIB_LoadTexture(GrassUp_png);
	texDirt = GRRLIB_LoadTexture(Dirt_png);
	texCobblestone = GRRLIB_LoadTexture(Cobblestone_png);
	texWoodenPlanks = GRRLIB_LoadTexture(Wood_png); //TODO: Change name of texture to "WoodenPlanks"
	texBedrock = GRRLIB_LoadTexture(Bedrock_png);
	
	GRRLIB_InitTileSet(tex_BMfont5, 8, 16, 0);
	GRRLIB_Settings.antialias = true;
	GRRLIB_SetBackgroundColour(3, 169, 244, 255);
	GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);
	GRRLIB_SetLightOff();
	
	/*
		Map
	*/
	for(int X = 0;X < sizex;X++){
		for(int Y = 0;Y < sizey;Y++){
			for(int Z = 0;Z < sizez;Z++){
			CurrentChunk[X][Y][Z] = 0;
			}
		}
	}
	for(int X = 0;X < sizex;X++){
		for(int Y = 0;Y < sizey;Y++){
			for(int Z = 0;Z < sizez;Z++){
			CurrentChunk[X][Y][Z] = 0;
			}
		}
	}
	lAX = lookingAtX;
	lAY = lookingAtY;
	lAZ = lookingAtZ;
	
	lwp_t thread;
	lwp_t chunk;
	LWP_MutexInit(&mutex, false);
	LWP_MutexInit(&chunkH, false);
	volatile int Temp = 1; //Pass in some usless data
	LWP_CreateThread(&thread, render, (void*)&Temp, NULL, 0, 80);
	LWP_CreateThread(&chunk, ChunkHandler, (void*)&Temp, NULL, 0, 80);
	
	//Input loop
	while(1){
		WPAD_ScanPads();
		pressedP1 = WPAD_ButtonsDown(0); //0 = Player 1
		WPAD_Expansion( 0, &data ); //Nunchuk
		WPAD_IR(0, &ir1);
		
		if (pressedP1) {
			if (pressedP1 & WPAD_BUTTON_HOME) {
				exit(0);
				
			} else if (pressedP1 & WPAD_BUTTON_HOME){
				running = false;
			} else if (pressedP1 & WPAD_BUTTON_B) {
				CurrentChunk[lookingAtX][lookingAtY][lookingAtZ] = 0;
			} else if (pressedP1 & WPAD_BUTTON_A) {
				CurrentChunk[lookingAtX][lookingAtY][lookingAtZ] = BlockInHand;
				save_used = true;
			} else if (pressedP1 & WPAD_BUTTON_MINUS) {
				if(lookingAtZ){
					lookingAtZ--;
					lookingAtZ--;
					CPz -= 5;
				}
			} else if (pressedP1 & WPAD_BUTTON_PLUS) {
				if(lookingAtZ != sizez){
					lookingAtZ++;
					lookingAtZ++;
					CPz += 5;
				}
			} else if (pressedP1 & WPAD_BUTTON_DOWN) {
				if(lookingAtX != sizex){
					lookingAtX++;
					lookingAtX++;
					CPx -= 5;
				}
			} else if (pressedP1 & WPAD_BUTTON_UP) {
				if(lookingAtX){
					lookingAtX--;
					lookingAtX--;
					CPx -= 5;
				}
			} else if (pressedP1 & WPAD_BUTTON_RIGHT) {

				if(!(lookingAtY == sizey)){
					lookingAtY++;
					lookingAtY++;
					CPy += 5;
				}
			} else if (pressedP1 & WPAD_BUTTON_LEFT) {
				if(lookingAtY){
					lookingAtY--;
					lookingAtY--;
					CPy -= 5;
				}
			} else if ((pressedP1 & WPAD_BUTTON_1) && (pressedP1 & WPAD_BUTTON_2)) {
				debug = !debug;
			} else if (pressedP1 & WPAD_BUTTON_1) { //NEEDS TO GET CLEANED UP
				if(BlockInHand == 5){
					if(!(BlockInHandFix == 4)){
						BlockInHandFix++;
					}
					else{
						BlockInHand++;
						if(BlockInHand == 5){
							BlockInHandFix--;
							BlockInHandFix--;
							BlockInHandFix--;
							BlockInHandFix--;
						}
					}
				}
				else{
					BlockInHand++;
				}
			} else if (pressedP1 & WPAD_BUTTON_2) {
				if((BlockInHand == 5) && !(BlockInHandFix == 0) ){
					if(!(BlockInHandFix == 0)){
						BlockInHandFix--;
					}
				}
				else if(BlockInHand){
					if(BlockInHand == 6){
						BlockInHand--;
						BlockInHandFix++;
						BlockInHandFix++;
					}
					else{
						BlockInHand--;
					}
			   }
			}
			if (data.type == WPAD_EXP_NUNCHUK) {
				if(data.nunchuk.js.pos.x - data.nunchuk.js.center.x  > 0 && (CameraRotY < 50)){
					CameraRotY++;
				}
				if(data.nunchuk.js.pos.x - data.nunchuk.js.center.x  < 0 && (CameraRotY > -50)){
					CameraRotY--;
				}
			}	
		}
	}
	
	/*
		Deinitialize
	*/
	LWP_MutexDestroy(mutex);
	GRRLIB_FreeTexture(tex_pointer1);
	GRRLIB_FreeTexture(tex_logo);
	GRRLIB_FreeTexture(tex_BMfont5);
	GRRLIB_FreeTexture(texStone);
	GRRLIB_FreeTexture(texGrassUp);
	GRRLIB_FreeTexture(texDirt);
	GRRLIB_FreeTexture(texCobblestone);
	GRRLIB_FreeTexture(texWoodenPlanks);
	GRRLIB_FreeTexture(texBedrock);
	Deinitialize();
}

/*
	u8 CalculateFrameRate()
	Used to calculate the framerate
*/
static u8 CalculateFrameRate() {
	static u8 frameCount = 0;
	static u32 lastTime;
	static u8 FPS = 0;
	u32 currentTime = ticks_to_millisecs(gettime());

	frameCount++;
	if(currentTime - lastTime > 1000) {
		lastTime = currentTime;
		FPS = frameCount;
		frameCount = 0;
	}
	return FPS;
}

/*
	WiiLight Functions
*/
void WIILIGHT_TurnOn()
{
	*(u32*)0xCD0000C0 |= 0x20;
}
void WIILIGHT_TurnOff()
{
	*(u32*)0xCD0000C0 &= ~0x20;
}
void WIILIGHT_SetLevel(int level)
{
	light_level = MIN(MAX(level, 0), 100);
	// Calculate the new on/off times for this light intensity
	u32 level_on;
	u32 level_off;
	level_on = (light_level * 2.55) * 40000;
	level_off = 10200000 - level_on;
	light_timeon.tv_nsec = level_on;
	light_timeoff.tv_nsec = level_off;
}


/*-- Smea's DSCraft map loader code --*/
/*int sizeX, sizeY;
int offsetX, offsetY;

typedef struct
{
	unsigned short sizeX, sizeY;
}header_struct;

header_struct *h;

unsigned char* readMap(char* filename)
{
	printf("opening %s\n",filename);
	FILE* f=fopen(filename,"rb");
	if(!f)return NULL;
	h=malloc(2048);
	fread(h,2048,1,f);
	sizeX=h->sizeX*4;
	sizeY=h->sizeY*4;
	printf("reading... %d %d\n", sizeX, sizeY);
	unsigned char* map=malloc(sizeX*sizeY*SIZEZ);
	printf("malloced\n");

	unsigned char data[1024];

	int x, y;
	for(x=0;x<sizeX/CLUSTERSIZE;x++)
	{
		for(y=0;y<sizeY/CLUSTERSIZE;y++)
		{
			fseek(f,2048+2048*(x+y*sizeX/CLUSTERSIZE),SEEK_SET);
			fread(data,1024,1,f);
			int i, j, k;
			for(i=0;i<CLUSTERSIZE;i++)
			{
				for(j=0;j<CLUSTERSIZE;j++)
				{
					for(k=0;k<SIZEZ;k++)
					{
						unsigned char d1=data[i+(j+k*CLUSTERSIZE)*CLUSTERSIZE];
						if(d1==13)d1=0;
						(map)[(x*CLUSTERSIZE+i)+((y*CLUSTERSIZE+j)+k*sizeY)*sizeX]=d1;
					}
				}
			}
		}
	}

	fclose(f);
	return map;
}*/