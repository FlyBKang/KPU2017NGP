#pragma once


#pragma comment(lib, "ws2_32")


#include <iostream>
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
//클라이언트 헤더 추가
#include <WinSock2.h>
#include <stdlib.h>
#include "Packets.h"

using namespace std;

#define TIME 33
#define MAX 200

#define WSIZE 500
#define CREATE_ZONE 550
#define BOUNDING_ZONE 600
#define UI_ZONE 50

#define PLAYER_SIZE 25.0f
#define BULLET_SIZE 5.0f

#define ROOT2 1.414f
#define ROOT3 1.732f
#define SPEED 3.0f
#define PLAYER_SPEED 3.5f

#define POSIT_RANDOM rand()%8 + 1
#define SPEED_RANDOM rand()%12 + 1

<<<<<<< HEAD
//클라이언트
#define SERVERIP	"127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512
=======
//클라 통신 위한 정의(send)   --11.29 02:55 -이정욱 
#define SERVERIP	"127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512

//-----------------------------------------
>>>>>>> ce28d3487d5930c4507db13840c04ef976e6c90d
