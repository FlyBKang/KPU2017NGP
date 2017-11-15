#include "stdafx.h"
#include "SceneMgr.h"



SceneMgr::SceneMgr()
{
	m_objectCnt = 0;
	m_Renderer = new Renderer(500, 500);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	
}


SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}


void SceneMgr::Update(float xvector, float yvector, DWORD time)
{
	CollisionCheckList();
	float timer = 0.0f;
	timer += float(time);
	
	//if (timer >= 0.005f)
	//{
	//	AddObjectList(0, 0, OBJECT_BULLET); //\dhfb
	//	SetObjCnt(GetObjCnt() + 1);
	//	timer = 0.0f;
	//}
	//0.5초마다 에로우 
	for (int i = 0; i < m_objectCnt; ++i)
	{
		if (m_objectList[i] != NULL)
		{
			DWORD CurrentTime = timeGetTime();
			if (CurrentTime - m_objectList[i]->GetObjectTimer() >= 500.f  && m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
			{
				AddObjectList(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(), OBJECT_ARROW,i); //\dhfb
				SetObjCnt(GetObjCnt() + 1);
				m_objectList[i]->SetTimer(timeGetTime());
				m_objectList[i]->SetMyFriend(i);
			}
		}

	}



	for (int i = 0; i< m_objectCnt; ++i)
	{



		//포지션 업데이트 루프 
		if (m_objectList[i] != NULL)
		{
			
			if (m_objectList[i]->GetLife() < 0.0001f || m_objectList[i]->GetLifeTime() <0.0001f)
			{

				delete m_objectList[i];
				m_objectList[i] = NULL;
			}
			else
			{
				m_objectList[i]->PositionUpdate(xvector, yvector, time);

			}
			 //시간추가 코드 
			//if (m_objectList[i]->GetObjectTimer() - timeGetTime() >= 5000.0f  && m_objectList[i]->GetObjectType()== OBJECT_CHARACTER)
			//{
			//	AddObjectList(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(), OBJECT_BULLET); //\dhfb
			//	SetObjCnt(GetObjCnt() + 1);
			//	m_objectList[i]->SetTimer(0.0f);
			//}
			
		}
	}

	

}
bool SceneMgr::CollisionCheck(Object *a, Object *b)
{
	float AlowerXbound = 0.0f;
	float AlowerYbound = 0.0f;
	float AHighXbound = 0.0f;
	float AHighYbound = 0.0f;

	float BlowerXbound = 0.0f;
	float BlowerYbound = 0.0f;
	float BHighXbound = 0.0f;
	float BHighYbound = 0.0f;

	
	AHighXbound = a->GetPositionX() + a->GetSize() / 2.f;
	AHighYbound = a->GetPositionY() + a->GetSize() / 2.f;

	AlowerXbound = a->GetPositionX() - a->GetSize() / 2.f;
	AlowerYbound = a->GetPositionY() - a->GetSize() / 2.f;

	BHighXbound = b->GetPositionX() + b->GetSize() / 2.f;
	BHighYbound = b->GetPositionY() + b->GetSize() / 2.f;

	BlowerXbound = b->GetPositionX() - b->GetSize() / 2.f;
	BlowerYbound = b->GetPositionY() - b->GetSize() / 2.f;
	
	if (AHighXbound < BlowerXbound)
	{
		return false;
	}
	if (AHighYbound < BlowerYbound)
	{
		return false;
	}
	if (AlowerYbound > BHighYbound)
	{
		return false;
	}
	if (AlowerXbound > BHighXbound)
	{
		return false;
	}
	return true;
}
void SceneMgr::Render()
{
	
	for (int i = 0; i < m_objectCnt; ++i)
	{
		if (m_objectList[i] != NULL)
		{
			if (m_objectList[i]->GetObjectType() == OBJECT_BULDING)
			{
				
				m_Renderer->DrawTexturedRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(),m_texCharacter);
			}
			else if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
			{

				m_Renderer->DrawTexturedRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA(), m_airCharacter);
			}

			else
			{
				m_Renderer->DrawSolidRect(m_objectList[i]->GetPositionX(), m_objectList[i]->GetPositionY(),
					m_objectList[i]->GetPositionZ(), m_objectList[i]->GetSize(), m_objectList[i]->GetR(),
					m_objectList[i]->GetG(), m_objectList[i]->GetB(), m_objectList[i]->GetA());
			}
		}
	}
}
void SceneMgr::CollisionCheckList()
{
	int collisionCount = 0;
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		collisionCount = 0;
		if (m_objectList[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				if (i == j)
					continue;

				if (m_objectList[j] != NULL)
				{
					if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[j]->GetObjectType() == OBJECT_BULLET)
					{

					}
					/*else
					{
						m_objectList[i]->SetRGBA(1, 0, 0, 1);
					}*/
					
					if (CollisionCheck(m_objectList[i],m_objectList[j]))
					{
						collisionCount++;
						if (m_objectList[i]->GetObjectType() == m_objectList[j]->GetObjectType() && m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
						{
							//m_objectList[i]->SetLife(m_objectList[i]->GetLife() - 1.f); 충돌데미지 없게
						}
						if (m_objectList[i]->GetObjectType() == OBJECT_BULDING && m_objectList[j]->GetObjectType() == OBJECT_CHARACTER)
						{
							m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
							
							m_objectList[j]->SetLife(0.0f);
						}
						if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER && m_objectList[j]->GetObjectType() == OBJECT_BULLET)
						{
							m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
							m_objectList[j]->SetLife(0.0f);
						}
						//에로우와 캐릭터
					/*	if(m_objectList[i]->GetObjectType() == OBJECT_CHARACTER && m_objectList[j]->GetObjectType() == OBJECT_ARROW)
						{
							m_objectList[i]->SetLife(m_objectList[i]->GetLife() - m_objectList[j]->GetLife());
							m_objectList[j]->SetLife(0.0f);
						}*/

					}
					else
					{
						//m_objectList[i]->SetRGBA(1,1,1,1);
						if (m_objectList[i]->GetObjectType() == OBJECT_CHARACTER)
							m_objectList[i]->SetRGBA(1, 1, 1, 1);
						if (m_objectList[i]->GetObjectType() == OBJECT_BULDING)
							m_objectList[i]->SetRGBA(1, 1, 0, 1);
					}
					
					
				}
			}

			if (collisionCount > 0)
			{
			
				//m_objectList[i]->SetRGBA(1, 0, 0, 1);
		
			}
			
		}
	}


}
int	SceneMgr::AddObjectList(float x, float y,int objecttype)
{
	//Find empty slot
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objectList[i] == NULL)
		{

			m_objectList[i] = new Object(x, y,objecttype);
			DWORD CreateObjectTime = timeGetTime();
			m_objectList[i]->SetTimer(CreateObjectTime);
			return i;
		}
	}

	//slots are full
	std::cout << "slots are full \n";
	return -1;
}
int	SceneMgr::AddObjectList(float x, float y, int objecttype,int friendnumber)
{
	//Find empty slot
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objectList[i] == NULL)
		{

			m_objectList[i] = new Object(x, y, objecttype, friendnumber);
			DWORD CreateObjectTime = timeGetTime();
			m_objectList[i]->SetTimer(CreateObjectTime);
			return i;
		}
	}

	//slots are full
	std::cout << "slots are full \n";
	return -1;
}
void SceneMgr::DeleteObject(int index)
{
	if (m_objectList[index] != NULL)
	{
		delete m_objectList[index];
		m_objectList[index] = NULL;
	}
}
void SceneMgr::DeleteOlderObject()
{
	for (int i = 0; i < m_objectCnt; ++i)
	{
		if (m_objectList[i] != NULL)
		{
			DeleteObject(rand() % m_objectCnt);
		}
	}
}