#ifndef __PLAYER_H__
#define __PLAYER_H__
struct Player_s{ //Player
	int x;
	int y;
	int z;
};
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

//Local
extern Player_s Player_l;
extern Velo_s Velo_l;
extern Gravity_s Gravity_L;

extern u32 LastRan;
extern u32 CurrentRun;

void* CalcPlayerPos(void* notUsed);

void InitPlayer(Player_s p, Gravity_s g);
Player_s GetPlayer();
Velo_s GetVelocity();
void UpdatePlayer(Player_s p, Velo_s v);
u32 GetOldTime();
u32 GetCurrentTime();
#endif