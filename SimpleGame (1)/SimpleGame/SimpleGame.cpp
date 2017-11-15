/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

//오브젝트 추가 코드
#include "Object.h"
#include "SceneMgr.h"
//

#include "Renderer.h"

Renderer *g_Renderer;
Object *g_Object = NULL;
//Object *mousobj = NULL;

SceneMgr* g_ScenMgr = NULL;

DWORD g_prevTime = NULL;

//Object *objectlist[1000];
static float frame;
static int objnum = 0;
bool g_LButtonDown;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	static int a = 0;
	a++;
	///////
	DWORD currentTime = timeGetTime();
	DWORD ElaspeTime = currentTime - g_prevTime;

	//if (currentTime > g_prevTime +15 )
	//{
	//	g_ScenMgr->AddObjectList(0, 0, OBJECT_BULLET); //\dhfb
	//	g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);
	//}

	
	
	//elsapse time curr time - gprevtime
	//updateall object
	//drawallobejct()

	////
	
	// Renderer Test
	
	/*g_Object->PositionUpdate(2.1f, 5.1f, frame);
	g_Renderer->DrawSolidRect(g_Object->GetPositionX(), g_Object->GetPositionY(), g_Object->GetPositionZ(), g_Object->GetSize(), 
		                      g_Object->GetR(), g_Object->GetG(), g_Object->GetB(), g_Object->GetA());*/
	
	

	//for (int i = 0; i < g_ScenMgr->GetObjCnt(); ++i)
	//{
	//	/*g_ScenMgr->m_objectList[i]->PositionUpdate(100.1f, 100.1f, ElaspeTime);*/
	//	
	//	g_Renderer->DrawSolidRect(g_ScenMgr->m_objectList[i]->GetPositionX(), g_ScenMgr->m_objectList[i]->GetPositionY(), g_ScenMgr->m_objectList[i]->GetPositionZ()
	//	, g_ScenMgr->m_objectList[i]->GetSize(), g_ScenMgr->m_objectList[i]->GetR(), g_ScenMgr->m_objectList[i]->GetG(), g_ScenMgr->m_objectList[i]->GetB(), g_ScenMgr->m_objectList[i]->GetA());
	//	
	//}
	g_ScenMgr->Update(1.0f, 1.0f, ElaspeTime);
	g_ScenMgr->Render();

	g_prevTime = currentTime;
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_LButtonDown = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && g_LButtonDown == true)
	{
		//Object* mousobj = new Object(x - 250, -y + 250, 0);
		//mousobj->SetSize(5.f);
		//mousobj->SetRGBA(1, 1, 1, 1);
		//10이상 없애는 코드 
	/*	if (10 <= g_ScenMgr->GetObjCnt() )
		{
			g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() - 1);
			g_ScenMgr->DeleteOlderObject();
			
		}*/

		g_ScenMgr->AddObjectList(x - 250, -y + 250,OBJECT_CHARACTER); //\dhfb
		g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);
		g_LButtonDown = false;
	}
	
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");
	
	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	g_ScenMgr = new SceneMgr;
	// Initialize Renderer
	/*g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}*/

	g_ScenMgr->AddObjectList(0, 0, OBJECT_BULDING); //\dhfb
	g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);
	frame = 1;

	g_ScenMgr->m_texCharacter = g_Renderer->CreatePngTexture("Texture/bunker.png");
	g_ScenMgr->m_airCharacter = g_Renderer->CreatePngTexture("Texture/airforce.png");

	//초기화

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	

	g_prevTime = timeGetTime();

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

