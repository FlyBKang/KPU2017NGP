#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(int x , int y)
{
	m_Renderer = new Renderer(x, y);

	if (m_Renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Render could not be initailized.\n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_objects[i] = NULL;
	}

	m_characterTexture = m_Renderer->CreatePngTexture("./Resource/plane.png");
	m_bulletTexture = m_Renderer->CreatePngTexture("./Resource/bullet.png");
}

SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}

int SceneMgr::CreateObject(float x, float y, int objectType, int teamType)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object(x, y, objectType, teamType);
			return i;
		}
	}

}

void SceneMgr::UpdateAllObject(float elapsedTime)
{
	DoColisionTest();

	enemyCooltime += elapsedTime * 0.001f;

	//적을 5초마다 한번씩 생성
	if (enemyCooltime > 5.f)
	{
		CreateObject(float( rand() % 250 - 250 ) , float  ( rand() % 200 + 50 ) , OBJECT_ARROW, TEAM_2);
		enemyCooltime = 0.f;
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL) {
			if (m_objects[i]->GetLife() < 0.0001f || m_objects[i]->GetLifeTime() < 0.0001f)
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
			else
			{
				m_objects[i]->Update(elapsedTime);

			}
		}
	}
}

void SceneMgr::DoColisionTest()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		collisionCount = 0;
		if (m_objects[i] != NULL)
		{
			for (int j = i + 1; j < MAX_OBJECTS_COUNT; j++)
			{
				if (m_objects[j] != NULL && m_objects[i] != NULL && m_objects[j]->GetTeamType() != m_objects[i]->GetTeamType())
				{
					if (BoxColisionTest(m_objects[i], m_objects[j]))
					{

						// 캐릭터 - 총알
						if (m_objects[i]->GetType() == OBJECT_CHARACTER && m_objects[j]->GetType() == OBJECT_BULLET)
						{
							m_objects[i]->SetDamage(m_objects[j]->GetLife());
							m_objects[j]->SetLife(0.f);
						}
						else if (m_objects[j]->GetType() == OBJECT_CHARACTER && m_objects[i]->GetType() == OBJECT_BULLET)
						{
							m_objects[j]->SetDamage(m_objects[i]->GetLife());
							m_objects[i]->SetLife(0.f);
						}

						// 캐릭터 - 화살
						else if (m_objects[i]->GetType() == OBJECT_CHARACTER && m_objects[j]->GetType() == OBJECT_ARROW )
						{
							if (m_objects[j]->GetParentID() != i)
							{
								m_objects[i]->SetDamage(m_objects[j]->GetLife());
								m_objects[j]->SetLife(0.f);

								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->GetParentID() == i)
										{
											m_objects[k]->SetParentID(-1);
										}
									}
								}
							}
						}
						else if (m_objects[j]->GetType() == OBJECT_CHARACTER && m_objects[i]->GetType() == OBJECT_ARROW)
						{
							if (m_objects[i]->GetParentID() != j)
							{
								m_objects[j]->SetDamage(m_objects[i]->GetLife());
								m_objects[i]->SetLife(0.f);
								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->GetParentID() == j)
										{
											m_objects[k]->SetParentID(-1);
										}
									}
								}
							}

						}
					}
				}
			}
			//if (collisionCount > 0)
			//{
			//}
			//else
			//{

			//	if (m_objects[i] != NULL && m_objects[i]->GetType() == OBJECT_BUILDING)
			//	{
			//		m_objects[i]->SetColor(1, 1, 0, 1);
			//	}
			//}
		}
	}
}


void SceneMgr::DrawAllObject()
{

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) 
	{
			if (m_objects[i] != NULL) 
			{
				if (m_objects[i]->GetType() == OBJECT_CHARACTER)
				{
					if (m_objects[i]->GetTeamType() == TEAM_1)
					{
						m_Renderer->DrawTexturedRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0, m_objects[i]->GetSize(), 1, 1, 1, 1, m_characterTexture);
					}
				}
				else
				{
					m_Renderer->DrawTexturedRect(m_objects[i]->GetPositionX(), m_objects[i]->GetPositionY(), 0, m_objects[i]->GetSize(), 1, 1, 1, 1, m_bulletTexture);

				}
			}
	}

}

bool SceneMgr::BoxColisionTest(Object* a, Object* b)
{
	if (a->GetPositionX() + a->GetHalfSize() < b->GetPositionX() - b->GetHalfSize()
			|| a->GetPositionX() - a->GetHalfSize() > b->GetPositionX() + b->GetHalfSize()) {
			return false;
		}

		if (a->GetPositionY() + a->GetHalfSize() < b->GetPositionY() - b->GetHalfSize()
			|| a->GetPositionY() - a->GetHalfSize() > b->GetPositionY() + b->GetHalfSize()) {
			return false;
		}

	return true;
}

void SceneMgr::DeleteObject(int index)
{
	if (m_objects[index] != NULL) {
		delete m_objects[index];
		m_objects[index] = NULL;
	}
}