#pragma once

#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
// 길찾기 알고리즘 등 여러가지가 들어감
// 이 클래스가 뚱뚱해지고 내용이 많아질 것임.

#define MAX_OBJECTS_COUNT 300

#define OBJECT_CHARACTER 0
#define OBJECT_BUILDING 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3



class SceneMgr
{

public:
	SceneMgr(int x , int y);
	~SceneMgr();


private:
	Object Obj[MAX_OBJECTS_COUNT];
	Object Player[3];
	GLuint m_characterTexture = 0;
	GLuint m_bulletTexture = 0;
	Renderer *m_Renderer = NULL;
};

