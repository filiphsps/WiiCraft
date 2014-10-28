/*									

	(c)Mojang AB And Filiph Sandström
									
									*/
#ifndef Blocks_H
#define Blocks_H

#include <iostream>

using namespace std;

class block {
	
	private:
		unsigned char id;
		string name;
		char textureX;
		char textureY;
		// dubble blockY = 0.15;
		
	public:
		block(string x,unsigned char id2);
		char getId();
		void changeId(unsigned char x);
		bool getNameById(int id);
		
};



#endif