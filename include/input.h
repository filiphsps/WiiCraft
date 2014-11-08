#ifndef __INPUT_H__
#define __INPUT_H__
/* Input */
struct Input_s{ 
	//Axis
	int main_x[3];      // UP & Down, Primary stick or nunchuck
	int main_y[3];      // LEFT & RIGHT, Primary stick or nunchuck
	int secondary_x[3]; // UP & Down, Secondary stick
	int secondary_y[3]; // LEFT & RIGHT, Secondary stick
	//Buttons
	bool A[3];
	bool B[3];
	bool PLUS[3];
	bool MINUS[3];
	bool HOME[3];
	bool C[3];
	bool Z[3];
	bool ZL[3];
	bool ZR[3];
};

void UpdateInput();
void RestAllButtons();
void InitInput(Input_s* input);
#endif