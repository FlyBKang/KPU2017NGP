#pragma once
#pragma once

//
#include "SceneMgr.h"
#include "Object.h"
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
	Object* player;
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
//Playerpacket *ToSeverPlayerPacket;
//ToSeverPlayerPacket->PlayerColor[0] = g_SceneMgr->m_objects[0]->GetColorRed;
//ToSeverPlayerPacket