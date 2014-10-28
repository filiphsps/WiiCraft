/*

	(c)2012-2014 Filiph Sandström & filfat Studio's

*/

#ifndef drawcube_H
#define drawcube_H

#include <iostream>
#include <grrlib.h>

using namespace std;

class drawcube {
	private:
		
	public:
		drawcube(int x,int z,int y);
		void drawcube_normal(int x,int z,int y);
		
		//Blocks:
		void drawcubeStone(int x, int z, int y/*, int font,int back,int top,int bottom,int left,int right*/);
		void drawcubeGrass(int x,int z,int y);
		void drawcubeDirt(int x,int z,int y);
		void drawcubeCobblestone(int x,int z,int y);
		void drawcubeWoodenplanks(int x,int z,int y);
		void drawcubeWoodenplanks2(int x,int z,int y);
		void drawcubeBedrock(int x,int z,int y);
};

#endif