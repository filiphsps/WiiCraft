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
#include "player.h"
#include "gamemanger.h"
#include "util.h"
#include "input.h"
#include "gui.h"

//Fonts:
#include "BMfont5_png.h"

//Images:
#include "pointer1_png.h"
#include "p1_png.h"
#include "Pointer_png.h"
#include "logo_png.h"

//Blocks:
#include "stone_png.h"
#include "grass_top_png.h"
#include "dirt_png.h"
#include "cobblestone_png.h"
#include "planks_oak_png.h"
#include "bedrock_png.h"
#include "LogUp_png.h"

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
bool save_used = true;
bool debug = true;
bool running = true;
u8 FPS = 0;
//Textures
GRRLIB_texImg *tex_pointer1;
GRRLIB_texImg *tex_pointer[3];
GRRLIB_texImg *texBlockPointer;
GRRLIB_texImg *tex_BMfont5;
GRRLIB_texImg *tex_logo;
GRRLIB_texImg *texBlock[63];

struct expansion_t data; //Nunchuks
//WiiLight
lwp_t light_thread = 0;
void *light_loop (void *arg);
vu32 *light_reg = (u32*) HW_GPIO;
bool light_on = false;
u8 light_level = 0;
struct timespec light_timeon = { 0 };
struct timespec light_timeoff = { 0 };
volatile u32 LastRan_l;
struct Screen_s{
	int h;
	int w;
};
/*
	Functions
*/
static u8 CalculateFrameRate();
void WIILIGHT_TurnOn();
void WIILIGHT_TurnOff();
void WIILIGHT_SetLevel(int level);

int CPx = 15;
int CPy = 0;
int CPz = 0;
float CameraRotY = 0;

/*
	Structs
*/
Player_s Player;
Velo_s Velo;
Gravity_s Gravity;
Input_s Input;
/*
	GUI/Video
*/
struct Camera_s{
	int upx;
	int upy;
	int upz;
	
	int lookx;
	int looky;
	int lookz;
};
Camera_s Camera;
Screen_s Screen;

/*
	World Related
*/
struct CurrentChunkTranslatestru{
	int x;
	int y;
	int z;
};
u8 CurrentChunk[sizex][sizey][sizez];
u8 CurrentChunkLook[sizex][sizey][sizez];

static mutex_t mutex;

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
	Debug("render(void): Configuring and starting \"rendering so called engine\"...");
	drawcube cube(Player.lX, Player.lY, Player.lZ);
	bool t, bo, f, ba, l, r;
	while (running){
		if(save_used){
			for(int z = 0; z < sizez; z++){
				for(int y = 0; y < sizey; y++){
					for(int x = 0; x < sizex; x++){
						if((CurrentChunk[x][y][z] > 0) && !(CurrentChunk[x][y][z] == 6)){
							if(CurrentChunk[x][y][z+1] > 0){
								t = false;
							}
							if(CurrentChunk[x][y][z-1] > 0){
								bo = false;
							}
							if(CurrentChunk[x+1][y][z] > 0){
								f = false;
							}
							if(CurrentChunk[x-1][y][z] > 0){
								ba = false;
							}
							if(CurrentChunk[x][y-1][z] > 0){
								l = false;
							}
							if(CurrentChunk[x][y+1][z] > 0){
								r = false;
							}
							cube.drawcubeBlock(x,y,z, texBlock[CurrentChunk[x][y][z]], t, bo, f, ba, l, r);
							t = true;
							bo = true;
							f = true;
							ba = true;
							l = true;
							r = true;
						}
					}
				}
			}
		}
		cube.drawcubeBlock(Player.lX,Player.lY, Player.lZ, texBlockPointer);
		GRRLIB_Camera3dSettings(Player.x, Player.y, Player.z + 4, 0,0,1, Player.x + Camera.lookx,Player.y + Camera.looky,Player.z + Camera.lookz);
		
		//Might aswell draw the text in this thread
		GRRLIB_2dMode();
		//RenderInventory();
		GRRLIB_DrawImg(Input.main_x[0], Input.main_y[0], tex_pointer[0], 0, 1, 1, WHITE);
		GRRLIB_DrawImg(640/2, 480/2, tex_pointer1, 0, 1, 1, WHITE);
		
		GRRLIB_Printf(17, 18, tex_BMfont5, WHITE, 1, "WiiCraft Dev Build");
		if(!Input.isNunchuck[0]){
			GRRLIB_Printf(240, 18, tex_BMfont5, WHITE, 1, "Please plugin a nunchuck");
		}
		
		if(!debug){
			GRRLIB_Printf(240, 18, tex_BMfont5, WHITE, 1, "Press 1+2 for debug information.");
		}
		else {
			GRRLIB_Printf(17, 39, tex_BMfont5, WHITE, 1, "FPS: %d", FPS);
			GRRLIB_Printf(17, 57, tex_BMfont5, WHITE, 1, "X: %d", static_cast<int>(Player.x));
			GRRLIB_Printf(17, 76, tex_BMfont5, WHITE, 1, "Y: %d", static_cast<int>(Player.y));
			GRRLIB_Printf(17, 95, tex_BMfont5, WHITE, 1, "Z: %d", static_cast<int>(Player.z));
			GRRLIB_Printf(17, 210, tex_BMfont5, WHITE, 1, "Velocity: %d, %d, %d", Velo.x, Velo.y, Velo.z);
			GRRLIB_Printf(17, 250, tex_BMfont5, WHITE, 1, "GameManager Time: %d %d", LastRan, CurrentRun);
			GRRLIB_Printf(17, 270, tex_BMfont5, WHITE, 1, "PrimaryX: %d, SecondaryX %d, CAMERX: %d", Input.main_x[0], Input.secondary_x[0], Camera.lookx);
            GRRLIB_Printf(17, 300, tex_BMfont5, WHITE, 1, "PrimaryY: %d, SecondaryY %d, CAMERY: %d", Input.main_y[0], Input.secondary_y[0], Camera.looky);
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
	Screen.h = rmode->xfbHeight;
	Screen.w = rmode->fbWidth;
	WIILIGHT_TurnOff();
	
	/*
		GRRLIB Related
	*/
	Debug("main(void): Configuring textures...");
	tex_pointer1 = GRRLIB_LoadTexture(pointer1_png);
	tex_pointer[0] = GRRLIB_LoadTexture(p1_png);
	texBlockPointer = GRRLIB_LoadTexture(Pointer_png);
	tex_BMfont5 = GRRLIB_LoadTexture(BMfont5_png);
	tex_logo = GRRLIB_LoadTexture(logo_png);
	
	texBlock[1] = GRRLIB_LoadTexture(stone_png);
	texBlock[2] = GRRLIB_LoadTexture(grass_top_png);
	texBlock[3] = GRRLIB_LoadTexture(dirt_png);
	texBlock[4] = GRRLIB_LoadTexture(cobblestone_png);
	texBlock[5] = GRRLIB_LoadTexture(planks_oak_png); //TODO: Change name of texture to "planks_oakenPlanks"
	texBlock[7] = GRRLIB_LoadTexture(bedrock_png);
	
	Debug("main(void): Configuring GRRLIB...");
	GRRLIB_InitTileSet(tex_BMfont5, 8, 16, 0);
	GRRLIB_Settings.antialias = true;
	GRRLIB_SetBackgroundColour(104,176,216,255);
	GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);
	GRRLIB_SetLightOff();
	
	/*
		Map
		Needs to be moved to a separate file
	*/
	Debug("main(void): Generating World...");
	for(int X = 0;X < sizex;X++){
		for(int Y = 0;Y < sizey;Y++){
			for(int Z = 0;Z < sizez;Z++){
			CurrentChunk[X][Y][Z] = 0;
			}
		}
	}
	for(int X = 0;X < sizex/8;X++){
		for(int Y = 0;Y < sizey/8;Y++){
			for(int Z = 30;Z <= 30;Z++){
			CurrentChunk[X][Y][Z] = 4;
			}
		}
	}
	
	/*
		Player Spawn Point
	*/
	Debug("main(void): Configuring Player...");
	Player.x = 10;
	Player.y = 8;
	Player.z = 30;
	
	Player.lX = 10;
	Player.lY = 8;
	Player.lZ = 30;
	
	/*
		World Gravity
	*/
	Debug("main(void): Configuring Gravity...");
	Gravity.x = 1;
	Gravity.y = 1;
	Gravity.z = 2;
	
	/*
		Camera Setup
	*/
	Debug("main(void): Configuring Camera...");
	Camera.lookx = -8;
	Camera.looky = 0;
	Camera.lookz = 0;
	
	Debug("main(void): Initializing Engine...");
	InitPlayer(&Player, &Gravity);
	InitInput(&Input);
	//InitGUI();
	
	lwp_t thread;
	volatile int Temp = 1; //Pass in some usless data
	Debug("main(void): Initializing & Starting Threads...");
	LWP_CreateThread(&thread, render, (void*)&Temp, NULL, 0, 64);
	//LWP_CreateThread(&chunk, ChunkHandler, (void*)&Temp, NULL, 0, 80);
	InitGMThread();
	
	//Input loop
	Debug("main(void): Entering input loop...");
	while(true){
		UpdateInput(); //Updates input
		
		if (Input.HOME[0]) {
			exit(0);
		}
		
		if (Input.B[0]) {
			CurrentChunk[Player.lX][Player.lY][Player.lZ] = 0;
		}
		else if (Input.A[0]) {
			CurrentChunk[Player.lX][Player.lY][Player.lZ] = BlockInHand;
			save_used = true;
		}
		
		if (Input.PLUS[0]) {
			if(Player.z != sizez){
				Player.z++;
				CPz -= 5;
			}
		}
		else if (Input.MINUS[0]) {
			if(Player.z){
				Player.z--;
				CPz += 5;
			}
		}
		
		if ((pressed[0] & WPAD_BUTTON_1) && (pressed[0] & WPAD_BUTTON_2)) {
			debug = !debug;
		}
		else if (pressed[0] & WPAD_BUTTON_1) { //NEEDS TO GET CLEANED UP
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
		}
		else if (pressed[0] & WPAD_BUTTON_2) {
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
		
		if(Input.Z[0]){
			Debug("main(void): Camera rotation resetted...");
			Camera.lookx = -8;
			Camera.looky = 0;
		} else if(Input.C[0]){
			Debug("main(void): Player position resetted...");
			Player.x = 10;
			Player.y = 8;
			Player.z = 31;
		}
		
		if(CurrentRun - LastRan_l >= 100){
			if (Input.secondary_x[0] < 100) {
				if(Player.x != sizex){
					Player.x++;
					CPx += 5;
				}
			}
			else if (Input.secondary_x[0] > 200) {
				if(Player.x){
					Player.x--;
					CPx -= 5;
				}
			}
			
			if (Input.secondary_y[0] > 200) {
				if(Player.y != sizex){
					Player.y++;
					CPy += 5;
				}
			}
			else if (Input.secondary_y[0] < 100) {
				if(Player.y){
					Player.y--;
					CPy -= 5;
				}
			}
		
			//Y
			if(Input.main_x[0] > 400 && !(Camera.looky >= 35)){
				Camera.looky++;
			}
			else if(Input.main_x[0] < 200 && !(Camera.looky <= -35)){
				Camera.looky--;
			}
			//X, TODO: fix the glitch when the both axis are moved
			/*if(Input.main_y[0] > 400 && !(Camera.lookx >= 5)){
				Camera.lookx++;
				if(Camera.lookx < -8){
					Camera.lookx += 10;
				}
			}
			else if(Input.main_y[0] < 200 && !(Camera.lookx <= -45)){
				Camera.lookx--;
				if(Camera.lookx < -8){
					Camera.lookx -= 10;
				}
			}*/
			LastRan_l = CurrentRun;
		}
	}
	Debug("main(void): Exited input loop...");
	
	/*
		Deinitialize
	*/
	Debug("main(void): Releasing textures...");
	LWP_MutexDestroy(mutex);
	GRRLIB_FreeTexture(tex_pointer1);
	GRRLIB_FreeTexture(tex_logo);
	GRRLIB_FreeTexture(tex_BMfont5);
	Debug("main(void): Calling Deinitialize()...");
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

	frameCount++;
	if(CurrentRun - lastTime > 1000) {
		lastTime = CurrentRun;
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
