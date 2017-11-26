/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "SceneMgr.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include <winUser.h>
using namespace std;
bool init = false;
SceneMgr *scene = new SceneMgr();
bool check_up;
bool check_down;
bool check_left;
bool check_right;
void keyInput()
{
	check_up = check_down = check_right = check_left = false;
	if (GetAsyncKeyState(VK_UP)) { check_up = true; }
	if (GetAsyncKeyState(VK_DOWN)) { check_down = true; }
	if (GetAsyncKeyState(VK_LEFT)) { check_left = true; }
	if (GetAsyncKeyState(VK_RIGHT)) { check_right = true; }
	if (check_up + check_down + check_right + check_left)
		scene->Update(check_up, check_down, check_left, check_right);
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if (!init)
	{
		scene->init();
		init = true;
		cout << "called" << endl;
	}
	keyInput();
	scene->Update();
	scene->Render();
	glutSwapBuffers();
}

void Idle(void)
{
}

void KeyInput(unsigned char key, int x, int y)
{

}

void SpecialKeyInput(int key, int x, int y)
{
	//	bool mixkey = false;
	//	if (key == GLUT_KEY_UP && key == GLUT_KEY_RIGHT)
	//	{
	//		scene->Update(true, false, true, false);
	//		mixkey = true;
	//	}
	//	if (key == GLUT_KEY_DOWN && key == GLUT_KEY_RIGHT)
	//	{
	//		scene->Update(false, true, true, false);
	//		mixkey = true;
	//	}
	//	if (key == GLUT_KEY_UP && key == GLUT_KEY_LEFT)
	//	{
	//		scene->Update(true, false, false, true);
	//		mixkey = true;
	//	}
	//	if (key == GLUT_KEY_DOWN && key == GLUT_KEY_LEFT)
	//	{
	//		scene->Update(false, true, false, true);
	//		mixkey = true;
	//	}
	//	if (mixkey)
	//		return;
	//	if (key == GLUT_KEY_UP)
	//		scene->Update(true, false, false, false);
	//	if (key == GLUT_KEY_DOWN)
	//		scene->Update(false, true, false, false);
	//	if (key == GLUT_KEY_RIGHT)
	//		scene->Update(false, false, false, true);
	//	if (key == GLUT_KEY_LEFT)
	//		scene->Update(false, false, true, false);
}


void RenderTime(int t)
{
	glutTimerFunc(TIME, RenderTime, 1);
	RenderScene();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 100);//optional
	glutInitWindowSize(WSIZE, WSIZE); //optional
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	scene->Rising();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	glutDisplayFunc(RenderScene);
	//glutKeyboardFunc(KeyInput);
	glutSpecialFunc(SpecialKeyInput);
	glutTimerFunc(TIME, RenderTime, 1);
	glutMainLoop();
	delete (scene);
    return 0;
}

