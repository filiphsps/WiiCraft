/*

	(c)2012-2014 Filiph Sandström & filfat Studio's

*/

#include <iostream>
#include <grrlib.h>
#include "drawcube.h"

//Blocks:
#include "Stone_png.h"
#include "GrassUp_png.h"
#include "Dirt_png.h"
#include "Cobblestone_png.h"
#include "Wood_png.h"
#include "WoodBirch_png.h"
#include "Bedrock_png.h"
#include "LogUp_png.h"

//Pointer for blocks:
#include "Pointer_png.h"

using namespace std;

drawcube::drawcube(int x, int z, int y){
	//
}

/* Stone */
void drawcube::drawcubeStone(int x, int z, int y){
	GRRLIB_texImg *Stone = GRRLIB_LoadTexture(Stone_png);
	GRRLIB_3dMode(0.1,1000,45,1,0);
	GRRLIB_SetTexture(Stone,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//back
	GX_Position3f32(1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//top
	GX_Position3f32(1.0f,1.0f,1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//bottom
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//left
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//right
	GX_Position3f32(1.0f,-1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	GX_End();
	GRRLIB_2dMode();
}
/* Grass */
void drawcube::drawcubeGrass(int x, int z, int y){
	GRRLIB_texImg *Grass = GRRLIB_LoadTexture(GrassUp_png);
	GRRLIB_3dMode(0.1,1000,45,1,0);
	GRRLIB_SetTexture(Grass,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//back
	GX_Position3f32(1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//top
	GX_Position3f32(1.0f,1.0f,1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//bottom
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//left
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//right
	GX_Position3f32(1.0f,-1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
}
/* Dirt */
void drawcube::drawcubeDirt(int x, int z, int y){
	GRRLIB_texImg *Dirt = GRRLIB_LoadTexture(Dirt_png);
	GRRLIB_3dMode(0.1,1000,45,1,0);
	GRRLIB_SetTexture(Dirt,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//back
	GX_Position3f32(1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//top
	GX_Position3f32(1.0f,1.0f,1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//bottom
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//left
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//right
	GX_Position3f32(1.0f,-1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	GX_End();
	GRRLIB_2dMode();
}
	
/* Cobblestone */
void drawcube::drawcubeCobblestone(int x, int z, int y){
	GRRLIB_texImg *terrain2 = GRRLIB_LoadTexture(Cobblestone_png);
	GRRLIB_3dMode(0.1,1000,45,1,0);
	GRRLIB_SetTexture(terrain2,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//back
	GX_Position3f32(1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//top
	GX_Position3f32(1.0f,1.0f,1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//bottom
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//left
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//right
	GX_Position3f32(1.0f,-1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	GX_End();
	GRRLIB_2dMode();
}

/* Wooden Planks */
void drawcube::drawcubeWoodenplanks(int x, int z, int y){
	GRRLIB_texImg *terrain2 = GRRLIB_LoadTexture(Wood_png);
	GRRLIB_3dMode(0.1,1000,45,1,0);
	GRRLIB_SetTexture(terrain2,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//back
	GX_Position3f32(1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//top
	GX_Position3f32(1.0f,1.0f,1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//bottom
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//left
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//right
	GX_Position3f32(1.0f,-1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	GX_End();
	GRRLIB_2dMode();
}

/* Wooden Planks(Birch) */
void drawcube::drawcubeWoodenplanks2(int x, int z, int y){
	GRRLIB_texImg *terrain2 = GRRLIB_LoadTexture(WoodBirch_png);
	GRRLIB_3dMode(0.1,1000,45,1,0);
	GRRLIB_SetTexture(terrain2,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//back
	GX_Position3f32(1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//top
	GX_Position3f32(1.0f,1.0f,1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//bottom
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//left
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//right
	GX_Position3f32(1.0f,-1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	GX_End();
	GRRLIB_2dMode();
}
	
/* Bedrock */
void drawcube::drawcubeBedrock(int x, int z, int y){
	GRRLIB_texImg *terrain2 = GRRLIB_LoadTexture(Bedrock_png);
	GRRLIB_3dMode(0.1,1000,45,1,0);
	GRRLIB_SetTexture(terrain2,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//back
	GX_Position3f32(1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//top
	GX_Position3f32(1.0f,1.0f,1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//bottom
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//left
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//right
	GX_Position3f32(1.0f,-1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	GX_End();
	GRRLIB_2dMode();
}

void drawcube::drawcube_normal(int x, int z, int y){
	GRRLIB_texImg *pointer = GRRLIB_LoadTexture(Pointer_png);
	GRRLIB_3dMode(0.1,1000,45,1,0);
	GRRLIB_SetTexture(pointer,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//back
	GX_Position3f32(1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//top
	GX_Position3f32(1.0f,1.0f,1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//bottom
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//left
	GX_Position3f32(-1.0f,1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(-1.0f,1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	//right
	GX_Position3f32(1.0f,-1.0f,-1.0f); 
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,-1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,0.0f);
	GX_Position3f32(-1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(1.0f,1.0f);
	GX_Position3f32(1.0f,-1.0f,1.0f);
	GX_Color1u32(0xFFFFFFFF);
	GX_TexCoord2f32(0.0f,1.0f);
	
	GX_End();
	GRRLIB_2dMode();
}