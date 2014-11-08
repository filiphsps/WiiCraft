#ifndef __PLAYER_H__
#define __PLAYER_H__
struct Player_s{ //Player
	/* The player cords */
	int x;
	int y;
	int z;
	
	/* The block-cords that the player is currently looking at */
	int lX;
	int lY;
	int lZ;
};
struct Gravity_s;
struct Velo_s;

void CalcPlayerPos();

void InitPlayer(Player_s* p, Gravity_s* g);
void UpdatePlayer(Player_s* p, Velo_s* v);
u32 GetOldTime();
u32 GetCurrentTime();
#endif