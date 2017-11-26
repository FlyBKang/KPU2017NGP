#pragma once

#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
// ��ã�� �˰��� �� ���������� ��
// �� Ŭ������ �׶������� ������ ������ ����.

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

