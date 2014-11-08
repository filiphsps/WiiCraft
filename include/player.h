#ifndef __PLAYER_H__
#define __PLAYER_H__
struct Player_s{ //Player
	int x;
	int y;
	int z;
};
struct Gravity_s;
struct Velo_s;

void CalcPlayerPos();

void InitPlayer(Player_s* p, Gravity_s* g);
void UpdatePlayer(Player_s* p, Velo_s* v);
u32 GetOldTime();
u32 GetCurrentTime();
#endif