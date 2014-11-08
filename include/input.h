#ifndef __INPUT_H__
#define __INPUT_H__
/* Input */
struct Input_s{ 
	//Axis
	int main_x;      // UP & Down, Primary stick or nunchuck
	int main_y;      // LEFT & RIGHT, Primary stick or nunchuck
	int secondary_x; // UP & Down, Secondary stick
	int secondary_y; // LEFT & RIGHT, Secondary stick
	//Buttons
	bool A;
	bool B;
	bool PLUS;
	bool MINUS;
	bool HOME;
	bool C;
	bool Z;
	bool ZL;
	bool ZR;
};

void UpdateInput();
void InitInput(Input_s* input);
#endif