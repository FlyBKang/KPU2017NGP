
#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr() {}
SceneMgr::~SceneMgr() { delete g_Renderer; }
void SceneMgr::Collision()
{
	if (!p.life)
		return;
	if (p.IsCollision)
		return;
	for (int i = 0; i < Obj_num; ++i)
	{
		if ((obj[i].X > p.X - PLAYER_SIZE / 2) && (obj[i].X < p.X + PLAYER_SIZE / 2))
			if ((obj[i].Y > p.Y - PLAYER_SIZE / 2) && (obj[i].Y < p.Y + PLAYER_SIZE / 2))
			{
				p.IsCollision = true;
				switch (POSIT_RANDOM)
				{
				case 1:
					obj[i].X = CREATE_ZONE / 2 + rand() % 50;
					obj[i].Y = 0 + rand() % 50;
					break;
				case 2:
					obj[i].X = CREATE_ZONE / 2 + rand() % 50;
					obj[i].Y = CREATE_ZONE / 2 + rand() % 50;
					break;
				case 3:
					obj[i].X = 0 + rand() % 50;
					obj[i].Y = CREATE_ZONE / 2 + rand() % 50;
					break;
				case 4:
					obj[i].X = -CREATE_ZONE / 2 + rand() % 50;
					obj[i].Y = CREATE_ZONE / 2 + rand() % 50;
					break;
				case 5:
					obj[i].X = -CREATE_ZONE / 2 + rand() % 50;
					obj[i].Y = 0 + rand() % 50;
					break;
				case 6:
					obj[i].X = -CREATE_ZONE / 2 + rand() % 50;
					obj[i].Y = -CREATE_ZONE / 2 + rand() % 50;
				case 7:
					obj[i].X = 0 + rand() % 50;
					obj[i].Y = -CREATE_ZONE / 2 + rand() % 50;
					break;
				case 8:
					obj[i].X = -CREATE_ZONE / 2 + rand() % 50;
					obj[i].Y = -CREATE_ZONE / 2 + rand() % 50;
					break;
				}
			}
	}
}
void SceneMgr::Update()
{
	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;
	//cout << (float)g_prevTime << endl;

	//충돌시 일어나는 일
	if (p.IsCollision)
	{
		if (p.life == 1)
		{
			p.life += -1;
			p.IsCollision = false;
		}
		if (g_prevTime >= collisionTime)
		{
			p.life += -1;
			p.IsCollision = false;
		}
	}
	else
		collisionTime = g_prevTime + 1000;

	for (int i = 0; i < Obj_num; ++i)
	{
		obj[i].X += obj[i].Vx;
		obj[i].Y += obj[i].Vy;

		if (obj[i].X > BOUNDING_ZONE / 2)
			obj[i].Vx = -obj[i].Vx;

		if (obj[i].X < -BOUNDING_ZONE / 2)
			obj[i].Vx = -obj[i].Vx;
		if (obj[i].Y > BOUNDING_ZONE / 2)
			obj[i].Vy = -obj[i].Vy;
		if (obj[i].Y < -BOUNDING_ZONE / 2)
			obj[i].Vy = -obj[i].Vy;
	}
}
void SceneMgr::init()
{
	p.num = 1;
	p.X = 0.0f;
	p.Y = 0.0f;
	p.R = 1.0f;
	p.G = 0.0f;
	p.B = 0.0f;
	for (int i = 0; i < MAX; ++i)
	{
		switch (POSIT_RANDOM)
		{
			case 1:
				obj[i].X = CREATE_ZONE/2+rand()%50;
				obj[i].Y = 0 + rand() % 50;
				break;
			case 2:
				obj[i].X = CREATE_ZONE/2 + rand() % 50;
				obj[i].Y = CREATE_ZONE/2 + rand() % 50;
				break;
			case 3:
				obj[i].X = 0 + rand() % 50;
				obj[i].Y = CREATE_ZONE/2 + rand() % 50;
				break;
			case 4:
				obj[i].X = -CREATE_ZONE/2 + rand() % 50;
				obj[i].Y = CREATE_ZONE/2 + rand() % 50;
				break;
			case 5:
				obj[i].X = -CREATE_ZONE/2 + rand() % 50;
				obj[i].Y = 0 + rand() % 50;
				break;
			case 6:
				obj[i].X = -CREATE_ZONE/2 + rand() % 50;
				obj[i].Y = -CREATE_ZONE/2 + rand() % 50;
			case 7:
				obj[i].X = 0 + rand() % 50;
				obj[i].Y = -CREATE_ZONE/2 + rand() % 50;
				break;
			case 8:
				obj[i].X = -CREATE_ZONE/2 + rand() % 50;
				obj[i].Y = -CREATE_ZONE/2 + rand() % 50;
				break;
		}
		switch (SPEED_RANDOM)
		{
		case 1:
			obj[i].Vx = ROOT3 * SPEED;
			obj[i].Vy = 1.0f * SPEED;
			break;
		case 2:
			obj[i].Vx = 1.0f* SPEED;
			obj[i].Vy = ROOT3* SPEED;
			break;
		case 3:
			obj[i].Vx = 0.0f* SPEED;
			obj[i].Vy = 2.0f* SPEED;
			break;
		case 4:
			obj[i].Vx = -1.0f* SPEED;
			obj[i].Vy = ROOT3* SPEED;
			break;
		case 5:
			obj[i].Vx = -ROOT3* SPEED;
			obj[i].Vy = 1.0f* SPEED;
			break;
		case 6:
			obj[i].Vx = -2.0f* SPEED;
			obj[i].Vy = 0.0f* SPEED;
			break;
		case 7:
			obj[i].Vx = -ROOT3* SPEED;
			obj[i].Vy = -1.0f* SPEED;
			break;
		case 8:
			obj[i].Vx = -1.0f* SPEED;
			obj[i].Vy = -ROOT3* SPEED;
			break;
		case 9:
			obj[i].Vx = 0.0f* SPEED;
			obj[i].Vy = -2.0f* SPEED;
			break;
		case 10:
			obj[i].Vx = 1.0f* SPEED;
			obj[i].Vy = -ROOT3* SPEED;
			break;
		case 11:
			obj[i].Vx = ROOT3* SPEED;
			obj[i].Vy = -1.0f* SPEED;
			break;
		case 12:
			obj[i].Vx = 2.0f* SPEED;
			obj[i].Vy = 0.0f* SPEED;
			break;
		}
	}
}
void SceneMgr::Render()
{
	if (p.life > 0)
	{
		if (p.IsCollision)
		{
			if (invincibility)
				invincibility = 0;
			else
				invincibility = 1;
			g_Renderer->DrawTexturedRect(p.X, p.Y, 0.0f, PLAYER_SIZE, 1.0f, 1.0f, 1.0f, invincibility, Object_Texture, 0.0f);
		}
		else
			g_Renderer->DrawTexturedRect(p.X, p.Y, 0.0f, PLAYER_SIZE, 1.0f, 1.0f, 1.0f, 1.0f, Object_Texture, 0.0f);
	}
	//(float x, float y, float z, float size, float r, float g, float b, float a, GLuint texID, float level
	for (int i = 0; i < Obj_num; ++i)
	{
		g_Renderer->DrawTexturedRect(obj[i].X, obj[i].Y, 0.0f, BULLET_SIZE, 1.0f, 1.0f, 1.0f, 1.0f, Object_Texture2, 0.1f);
	}
}
void SceneMgr::Update(bool up, bool down, bool left, bool right)
{
	if (up)
	{
		p.Y += PLAYER_SPEED;
	}
	if (down)
	{
		p.Y += -PLAYER_SPEED;
	}
	if (left)
	{
		p.X += -PLAYER_SPEED;
	}
	if (right)
	{
		p.X += PLAYER_SPEED;
	}
}