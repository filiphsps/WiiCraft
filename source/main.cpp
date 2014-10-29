/*

	(c)2012-2014 Filiph Sandström & filfat Studio's

*/

//Standard libray:
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <malloc.h>
#include <time.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp.h>
#include <ogc/lwp_watchdog.h>
#include <sdcard/wiisd_io.h>
#include <ogc/usbstorage.h>
#include <ogcsys.h>
#include <wiiuse/wpad.h>
#include <errno.h>

//Network:
#include <network.h>

//GRRLIB:
#include <grrlib.h>

//Classes:
#include "Blocks.h"
#include "drawcube.h"
#include "debug.h"
#include "camera.h"
#include "init.h"

//Fonts:
#include "BMfont5_png.h"

//Images:
#include "pointer1_png.h"
#include "Pointer_png.h"

//Blocks:
#include "Stone_png.h"
#include "GrassUp_png.h"
#include "Dirt_png.h"
#include "Cobblestone_png.h"
#include "Wood_png.h"
#include "WoodBirch_png.h"
#include "Bedrock_png.h"
#include "LogUp_png.h"

//RGBA Colors
#define BLACK   0x000000FF
#define MAROON  0x800000FF
#define GREEN   0x008000FF
#define OLIVE   0x808000FF
#define NAVY    0x000080FF
#define PURPLE  0x800080FF
#define TEAL    0x008080FF
#define GRAY    0x808080FF
#define SILVER  0xC0C0C0FF
#define RED     0xFF0000FF
#define LIME    0x00FF00FF
#define YELLOW  0xFFFF00FF
#define BLUE    0x0000FFFF
#define FUCHSIA 0xFF00FFFF
#define AQUA    0x00FFFFFF
#define WHITE   0xFFFFFFFF

//Wiilight
#define HW_GPIO             0xCD0000C0;
#define DISC_SLOT_LED       0x20

extern "C" {
	extern void __exception_setreload(int t);
}

using namespace std;

const int sizex = 32;
const int sizey = 32;
const int sizez = 64;
const int SIZEZ = 64;

ir_t ir1;

/*
	WiiLight
*/
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


struct WorldTranslatestru{
	int x;
	int y;
	int z;
};

u8 World[sizex][sizey][sizez];
u8 WorldLook[sizex][sizey][sizez];

/*
	int main()
	The main function
*/

int main()  {
	// In the event of a code dump, the app will exit after 10 seconds (unless the user presses POWER)
	__exception_setreload(10);
	
	/*
		Initialize
	*/
	WIILIGHT_SetLevel(255);
	WIILIGHT_TurnOn();
	
	Initialize();

	WIILIGHT_TurnOff();

	u8 FPS = 0;
	int BlockInHand = 1;
	int BlockInHandFix = 0;
	int lookingAtX = 16;
	int lookingAtY = 16;
	int lookingAtZ = 32;
	bool save_used = false;
	bool debug = false;
	bool running = true;
	WPAD_IR(WPAD_CHAN_1, &ir1);
	
	/*
		GRRLIB Related
	*/
	GRRLIB_texImg *tex_pointer1 = GRRLIB_LoadTexture(pointer1_png);
	GRRLIB_texImg *texBlockPointer = GRRLIB_LoadTexture(Pointer_png);
	GRRLIB_texImg *tex_BMfont5 = GRRLIB_LoadTexture(BMfont5_png);
	
	GRRLIB_texImg *texStone = GRRLIB_LoadTexture(Stone_png);
	GRRLIB_texImg *texGrassUp = GRRLIB_LoadTexture(GrassUp_png);
	GRRLIB_texImg *texDirt = GRRLIB_LoadTexture(Dirt_png);
	GRRLIB_texImg *texCobblestone = GRRLIB_LoadTexture(Cobblestone_png);
	GRRLIB_texImg *texWoodenPlanks = GRRLIB_LoadTexture(Wood_png); //TODO: Change name of texture to "WoodenPlanks"
	GRRLIB_texImg *texBedrock = GRRLIB_LoadTexture(Bedrock_png);
	
	GRRLIB_InitTileSet(tex_BMfont5, 8, 16, 0);
	GRRLIB_Settings.antialias = true;
	GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
	GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);
	GRRLIB_SetLightOff();
	
	/*
		Blocks
	*/
	block Stone("Stone", 1);
	block Grass("Grass", 2);
	block Dirt("Dirt", 3);
	block CobbleStone("CobbleStone", 4);
	
	/*
		Map
	*/
	for(int X = 0;X < sizex;X++){
		for(int Y = 0;Y < sizey;Y++){
			for(int Z = 0;Z < sizez;Z++){
			World[X][Y][Z] = 0;
			}
		}
	}
	/*u8 WorldFix[sizex][sizey][sizez];
	for(int X = 0;X < sizex;X++){
		for(int Y = 0;Y < sizey;Y++){
			for(int Z = 0;Z < sizez;Z++){
			World[X][Y][Z] = 0;
			}
		}
	}*/

	for(int X = 0;X < sizex;X++){
		for(int Y = 0;Y < sizey;Y++){
			for(int Z = 0;Z < sizez;Z++){
			World[X][Y][Z] = 0;
			}
		}
	}
	
	//Draw Cube
	drawcube cube(lookingAtX, lookingAtZ, lookingAtY);

	/*
		Camera Related
	*/
	int upx = 0;
	int upy = 1;
	int upz = 0;
	int lAX = lookingAtX;
	int lAY = lookingAtY;
	//int lAZ = lookingAtZ;
	
	while (running){
		lAX = lookingAtX;
		lAY = lookingAtY;
		//lAZ = lookingAtZ;
		
		WPAD_ScanPads();
		u32 pressed = WPAD_ButtonsDown(0); //0 = Player 1
		WPAD_IR(0, &ir1);
		GRRLIB_Camera3dSettings(lAX,lAY,sizez, upx,upy,upz, lookingAtX,lookingAtY,lookingAtZ);
		
		GRRLIB_2dMode();
		GRRLIB_DrawImg(ir1.sx - 48, ir1.sy - 45, tex_pointer1, 0, 1, 1, 0xffffffff);
		
		GRRLIB_3dMode(0.1, 1000, 45, 1, 0);
        GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);
		
		if (pressed) {
			if (pressed & WPAD_BUTTON_HOME) {
				exit(0);
			} else if (pressed & WPAD_BUTTON_HOME){
				running = false;
			} else if (pressed & WPAD_BUTTON_B) {
				World[lookingAtX][lookingAtY][lookingAtZ] = 0;
			} else if (pressed & WPAD_BUTTON_A) {
				World[lookingAtX][lookingAtY][lookingAtZ] = BlockInHand;
				save_used = true;
				if(World[lookingAtX][lookingAtY][lookingAtZ] == 5){
					//WorldFix[lookingAtX][lookingAtY][lookingAtZ] = BlockInHandFix;
				}
			} else if (pressed & WPAD_BUTTON_MINUS) {
				if(lookingAtZ){
					lookingAtZ--;
					lookingAtZ--;
				}
			} else if (pressed & WPAD_BUTTON_PLUS) {
				if(lookingAtZ != sizez){
					lookingAtZ++;
					lookingAtZ++;
				}
			} else if (pressed & WPAD_BUTTON_UP) {
				if(lookingAtY != sizey){
					lookingAtY++;
					lookingAtY++;
				}
			} else if (pressed & WPAD_BUTTON_DOWN) {
				if(lookingAtY){
					lookingAtY--;
					lookingAtY--;
				}
			} else if (pressed & WPAD_BUTTON_RIGHT) {

				if(!(lookingAtX == sizex)){
					lookingAtX++;
					lookingAtX++;
				}
			} else if (pressed & WPAD_BUTTON_LEFT) {
				if(lookingAtX){
					lookingAtX--;
					lookingAtX--;
				}
			} else if ((pressed & WPAD_BUTTON_1) && (pressed & WPAD_BUTTON_2)) {
				debug = !debug;
			} else if (pressed & WPAD_BUTTON_1) {
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
			} else if (pressed & WPAD_BUTTON_2) {
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
		}
		int Duh = 0;
		if(save_used){
			for(int x = 0;x < sizex; x++){
				for(int y = 0;y < sizey; y++){
					for(int z = 0;z < sizez; z++){
						/*bool t = true;
						bool bo = true;
						bool f = true;
						bool ba = true;
						bool l = true;
						bool r = true;*/
						switch((World[x][y][z])){
						case 0:
						break;
						case 1:
							/* Stone: */
							
							cube.drawcubeBlock(x,z,y, texStone);
							break;
						case 2:
							/* Grass: */
							/*if(World[x][y][z + 2] > 0){ //TODO
								t = false;
							}
							if(World[x][y][z - 2] > 0){
								bo = false;
							}
							if(World[x][y + 2][z] > 0){
								f = false;
							}
							if(World[x][y - 2][z] > 0){
								ba = false;
							}
							if(World[x - 2][y][z] > 0){
								l = false;
							}
							if(World[x + 2][y][z] > 0){
								r = false;
							}
							cube.drawcubeTestBlock(x,z,y, texGrassUp, t, bo, f, ba, l, r);*/
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
		
		GRRLIB_2dMode();
		
		GRRLIB_Printf(17, 18, tex_BMfont5, WHITE, 1, "WiiCraft 0.8.0.0 Dev");
		if(!debug){
			GRRLIB_Printf(240, 18, tex_BMfont5, WHITE, 1, "Press 1+2 for debug information.");
		}
		else {
			GRRLIB_Printf(17, 39, tex_BMfont5, WHITE, 1, "FPS: %d", FPS);
			GRRLIB_Printf(17, 57, tex_BMfont5, WHITE, 1, "X: %d", static_cast<int>(lookingAtX));
			GRRLIB_Printf(17, 76, tex_BMfont5, WHITE, 1, "Y: %d", static_cast<int>(lookingAtY));
			GRRLIB_Printf(17, 95, tex_BMfont5, WHITE, 1, "Z: %d", static_cast<int>(lookingAtZ));
			GRRLIB_Printf(17, 395, tex_BMfont5, WHITE, 1, "Duh: %d", static_cast<int>(Duh));
			FPS = CalculateFrameRate();
		}
		GRRLIB_Printf(17, 114, tex_BMfont5, WHITE, 1, "Current block in hand: %d:%d", static_cast<int>(BlockInHand),BlockInHandFix);
		
		GRRLIB_Render();
	}
	
	/*
		Deinitialize
	*/
	GRRLIB_FreeTexture(tex_pointer1);
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