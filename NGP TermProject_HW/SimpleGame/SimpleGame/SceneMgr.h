#pragma once
#include "Object.h"
#include "Player.h"
#include "Renderer.h"
#include <windows.h>
class SceneMgr
{
	bool invincibility			=0;
	DWORD g_prevTime			=0;
	DWORD currTime				=0;
	DWORD elapsedTime			=0;
	DWORD collisionTime			=0;
public:
	int Obj_num = 75;
	Renderer *g_Renderer;
	GLuint Object_Texture = NULL;
	GLuint Object_Texture2 = NULL;
	Player p;
	Object obj[MAX];
	void Rising(){
		g_Renderer = new Renderer(WSIZE, WSIZE);
		Object_Texture = g_Renderer->CreatePngTexture("Textures/Plane.png");
		Object_Texture2 = g_Renderer->CreatePngTexture("Textures/bullet.png");
	};
	void Collision();
	void init();
	void Update();
	void Update(bool up, bool down, bool left, bool right);
	void Render();
	SceneMgr();
	~SceneMgr();
};
