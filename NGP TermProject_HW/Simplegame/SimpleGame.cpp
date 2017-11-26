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
#include "SceneMgr.h"


SceneMgr *g_SceneMgr = NULL;
bool g_LButtonDown = false;
float g_mouseCooltime = 0.f;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
}

void KeyInput(unsigned char key, int x, int y)
{
	//	if( key == GLUT_KEY_UP )
	//		g_SceneMgr->
	//	if (key == GLUT_KEY_RIGHT)
	//		g_SceneMgr->
	//	if (key == GLUT_KEY_DOWN)
	//		g_SceneMgr->
	//	if (key == GLUT_KEY_LEFT)
	//		g_SceneMgr->
}

void SpecialKeyInput(int key, int x, int y)
{
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WSIZE, WSIZE);
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


	glutDisplayFunc(RenderScene);
	//glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

   g_SceneMgr = new SceneMgr(WSIZE,WSIZE);


	glutMainLoop();

	delete g_SceneMgr;

    return 0;
}

