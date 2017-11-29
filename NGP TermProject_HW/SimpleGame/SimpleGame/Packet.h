#pragma once
#include "Player.h"
struct Playerpacket
{
	int PlayerNum;
	float PlayerColor[3];
	float PlayerPosition[2];
	int     PlayerLife;
	int   PlayerScore;
	bool  isCollide;
};

struct TimePacket
{
	float time;
};

struct End
{
	Player* player;
	float Endtime;
	bool isEnd;
};
struct KeyState
{
	bool isKeyUp;
	bool isKeyLeft;
	bool isKeyDown;
	bool isKeyRight;
};