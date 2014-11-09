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
		void drawcubeBlock(int x, int y, int z, GRRLIB_texImg* Block);
		void drawcubeBlock(int x, int y, int z, GRRLIB_texImg* Block, bool t, bool bo, bool f, bool ba, bool l, bool r);
};

#endif