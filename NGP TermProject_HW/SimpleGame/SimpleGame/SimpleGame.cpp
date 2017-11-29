/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

<<<<<<< HEAD
///////////////////////////////////////
=======




>>>>>>> ce28d3487d5930c4507db13840c04ef976e6c90d
#include "stdafx.h"
#include "SceneMgr.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
<<<<<<< HEAD
// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

//
=======

//Ŭ�� ��� ���� ���(send)   --11.29 02:55 -������ - ��������� �߰��ص� COLORBIT�� define�� ���� ��� ���ð��ӿ��� ���� �����̾ƴ� 
								//���� ���� �ڵ忡 ������ ���̴� �������� ���� �ϴ� ���� ���� �� ����.
//#pragma comment(lib, "ws2_32")
//#include <WinSock2.h>
//#include <stdlib.h>
#include "Packet.h"
#include "Player.h"
void err_quit(char *msg);
void err_display(char* msg);
int PacketToServer();
//---------------------


>>>>>>> ce28d3487d5930c4507db13840c04ef976e6c90d
bool init = false;
SceneMgr *scene = new SceneMgr();
SendToServer SendToServerPackets;

void keyInput()
{
	SendToServerPackets.key.up = SendToServerPackets.key.down = false;
	SendToServerPackets.key.right = SendToServerPackets.key.left = false;
	if (GetAsyncKeyState(VK_UP)) { SendToServerPackets.key.up = true; }
	if (GetAsyncKeyState(VK_DOWN)) { SendToServerPackets.key.down = true; }
	if (GetAsyncKeyState(VK_LEFT)) { SendToServerPackets.key.left = true; }
	if (GetAsyncKeyState(VK_RIGHT)) { SendToServerPackets.key.right = true; }
	// ���� Ű�Է� ó��
	//if (KS.check_up + KS.check_down + KS.check_right + KS.check_left)
	//	scene->Update(KS.check_up, KS.check_down, KS.check_left, KS.check_right);
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
	scene->Collision();
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
	//
	//Ŭ���̾�Ʈ ���
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;


	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// ������ ��ſ� ����� ����
	char buf[BUFSIZE];

	//-------------------------------------

	//-------------------------------------

	// ������ ������ ���
	// send() & recv �� ����� �κ�

	//

	//closesocket()
	closesocket(sock);

	//���� ����
	WSACleanup();

	//
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
	////====================================================================================
	//Ŭ�� ��� ���� �Լ� ����(send)   --11.29 02:55 -������ 
	//PacketToServer(argc, *argv);
	//====================================================================================
	glutDisplayFunc(RenderScene);
	//glutKeyboardFunc(KeyInput);
	glutSpecialFunc(SpecialKeyInput);
	glutTimerFunc(TIME, RenderTime, 1);
	glutMainLoop();
	delete (scene);
    return 0;
}

//====================================================================================
//Ŭ�� ��� ���� �Լ� ����(send)   --11.29 02:55 -������ 
//void err_quit(char *msg)
//{
//	LPVOID lpMsgBuf;
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),  //GetLastError���� ���� 
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPSTR)&lpMsgBuf, 0, NULL);
//	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPSTR)msg, MB_ICONERROR);
//	LocalFree(lpMsgBuf);
//	exit(1);
//}
//// ���� �Լ� ���� ���
//void err_display(char* msg)
//{
//	LPVOID lpMsgBuf;
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPWSTR)&lpMsgBuf, 0, NULL);
//	printf("[%s] %s", msg, (char *)lpMsgBuf);
//	LocalFree(lpMsgBuf);
//}
//int PacketToServer()  // ������� ���� �ǵ��ϼ� ����. 
//{
//	int retval;
//
//	// ���� �ʱ�ȭ
//	WSADATA wsa;
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//		return 1;
//
//
//	// socket()
//	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
//	if (sock == INVALID_SOCKET) err_quit("socket()");
//
//	// connect()
//	SOCKADDR_IN serveraddr;
//	ZeroMemory(&serveraddr, sizeof(serveraddr));
//	serveraddr.sin_family = AF_INET;
//	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
//	serveraddr.sin_port = htons(SERVERPORT);
//	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
//	if (retval == SOCKET_ERROR) err_quit("connect()");
//
//
//	// ������ ��ſ� ����� ����
//	char buf[BUFSIZE];
//
//	//-------------------------------------
//
//	//-------------------------------------
//
//	// ������ ������ ���
//	// send() & recv �� ����� �κ�
//
//	//
//
//	//closesocket()
//	closesocket(sock);
//
//	//���� ����
//	WSACleanup();
//	return 0;
//
//}
//---------------------------------------------------------------------------