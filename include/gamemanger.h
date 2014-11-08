#ifndef __GM_H__
#define __GM_H__
struct Velo_s{ //Velcoity
	int x;
	int y;
	int z;
};
struct Gravity_s{ //The current gravity. Could alse be refered to as "Friction"
	int x;
	int y;
	int z;
};

extern int TestingGM;
extern volatile u32 LastRan;
extern volatile u32 CurrentRun;

void* GameManager(void* notUsed);
void InitGMThread(void);
void StopGMThread(void);
#endif