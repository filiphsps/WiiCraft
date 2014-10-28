/*									

	(c)Mojang AB And Filiph Sandström
									
									*/
#include <iostream>
#include "Blocks.h"

using namespace std;

block::block(string x, unsigned char id2){
	name = x;
	id = id2;
	
}

char block::getId(){
	int x = id;
	return static_cast<int>(x);
	
}

void block::changeId(unsigned char x){
	x = id;
	
}

bool block::getNameById(int id2){
	bool name = false;
	if(id == id2)name = true;
	return name;
}