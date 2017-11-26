
#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(int x , int y)
{
	m_Renderer = new Renderer(x, y);

	if (m_Renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Render could not be initailized.\n";
	}


	m_characterTexture = m_Renderer->CreatePngTexture("./Resource/plane.png");
	m_bulletTexture = m_Renderer->CreatePngTexture("./Resource/bullet.png");
}


//	void SceneMgr::DoColisionTest()
//	{
//		
//	}
//	
//	
//	void SceneMgr::DrawAllObject()
//	{
//	
//	}
//	
//	bool SceneMgr::BoxColisionTest(Object* a, Object* b)
//	{
//		
//	}
//	
//	void SceneMgr::DeleteObject(int index) 
//	{
//	}
SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}