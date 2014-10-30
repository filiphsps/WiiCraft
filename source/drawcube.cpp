/*

	(c)2012-2014 Filiph Sandström & filfat Studio's

*/

#include <iostream>
#include <grrlib.h>
#include "drawcube.h"


using namespace std;

drawcube::drawcube(int x, int z, int y){
	//
}

/* Function to render blocks */
void drawcube::drawcubeBlock(int x, int z, int y, GRRLIB_texImg* Block){
	GRRLIB_3dMode(0.1, 1000, 45, 1, 0);
	GRRLIB_SetTexture(Block,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);

	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	/* Top */
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

	/* Bottom */
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

	/* Front */
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

	/* Back */
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

	/* Left */
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

	/* Right */
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

/* Test Function to render blocks */
void drawcube::drawcubeBlock(int x, int z, int y, GRRLIB_texImg* Block, bool t, bool bo, bool f, bool ba, bool l, bool r){
	//TODO: Correct the sides
	
	GRRLIB_3dMode(0.1, 1000, 45, 1, 0);
	GRRLIB_SetTexture(Block,0);
	GRRLIB_ObjectView(x,y,z, 0,0,0, 1,1,1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
	
	/* Top */
	if(t){
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
	}

	/* Bottom */
	if(bo){
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
	}

	/* Front */
	if(f){
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
	}
	
	/* Back */
	if(ba){
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
	}
	
	/* Left */
	if(l){
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
	}

	/* Right */
	if(r){
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
	
	GX_End();
	GRRLIB_2dMode();
}