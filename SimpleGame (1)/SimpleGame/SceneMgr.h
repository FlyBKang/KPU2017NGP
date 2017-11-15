#pragma once
#include "Object.h"
#include "Renderer.h"



class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();
public:
	Object* m_objectList[MAX_OBJECTS_COUNT];
	
private:
	int		m_objectCnt;
	Renderer *m_Renderer;
	
public:
	void Update(float xvector, float yvector, DWORD time);
	void Render();
	bool CollisionCheck(Object *a, Object *b);
	void CollisionCheckList();
	int	 AddObjectList(float x, float y,int objecttype);
	int	 AddObjectList(float x, float y, int objecttype, int friendnumber);
	void DeleteObject(int index);
	void DeleteOlderObject();
	GLuint m_texCharacter;
	GLuint m_airCharacter;
public:
	inline void SetObjCnt(int cnt) { m_objectCnt = cnt; };
	inline int GetObjCnt() { return m_objectCnt; };
};

