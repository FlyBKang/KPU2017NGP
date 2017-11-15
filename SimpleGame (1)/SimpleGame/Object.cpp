#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_Life = 100.f;
	m_LifeTime = 100000.f;
	m_objectTimer = 0.00000f;
}
Object::Object(float x, float y,int objecttype)
{
	m_objectTimer = 0.00000f;
	if (objecttype == OBJECT_BULDING)
	{
		m_type = OBJECT_BULDING;
		m_x = 0, m_y = 0;
		m_Life = 500.f;
		m_Speed = 0.f;
		m_size = 50.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1,1,0,1);
		m_LifeTime = 100000.f;
		return;
	}
	else if (objecttype == OBJECT_CHARACTER)
	{
		m_type = OBJECT_CHARACTER;
		
		m_Life = 10.f;
		m_Speed = 300.f;
		m_size = 40.f;
		m_r = 1.f;
		m_g = 1.f;
		m_b = 1;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		return;
	}
	else if (objecttype == OBJECT_BULLET)
	{
		m_type = OBJECT_BULLET;
	
		m_Life = 20.f;
		m_Speed = 300.f;
		m_size = 2.f;
		m_r = 1.f;
		m_g = 0;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		return;
	}
	else if (objecttype == OBJECT_ARROW)
	{
		m_type = OBJECT_ARROW;

		m_Life = 20.f;
		m_Speed = 300.f;
		m_size = 2.f;
		m_r = 0;
		m_g = 1.f;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		return;
	}
	
	
	

}

Object::Object(float x, float y, int objecttype,int friendnumber)
{
	m_objectTimer = 0.00000f;
	if (objecttype == OBJECT_BULDING)
	{
		m_type = OBJECT_BULDING;
		m_x = 0, m_y = 0;
		m_Life = 500.f;
		m_Speed = 0.f;
		m_size = 50.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1, 1, 0, 1);
		m_LifeTime = 100000.f;
		return;
	}
	else if (objecttype == OBJECT_CHARACTER)
	{
		m_type = OBJECT_CHARACTER;

		m_Life = 10.f;
		m_Speed = 300.f;
		m_size = 10.f;
		m_r = 1.f;
		m_g = 1.f;
		m_b = 1;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		return;
	}
	else if (objecttype == OBJECT_BULLET)
	{
		m_type = OBJECT_BULLET;

		m_Life = 20.f;
		m_Speed = 300.f;
		m_size = 2.f;
		m_r = 1.f;
		m_g = 0;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		return;
	}
	else if (objecttype == OBJECT_ARROW)
	{
		m_type = OBJECT_ARROW;

		m_Life = 20.f;
		m_Speed = 300.f;
		m_size = 2.f;
		m_r = 0;
		m_g = 1.f;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		return;
	}




}



Object::~Object()
{
	//if (m_Life < 0)
	//	delete this;
}
void Object::PositionUpdate(float xvector, float yvector, DWORD time)
{
	float elapsetime = (float)time * 0.00001f;


	m_x = m_x + m_Vx *(xvector * elapsetime) * m_Speed;
	m_y = m_y + m_Vy *(yvector * elapsetime) * m_Speed;
	//m_size = 20 * sin(m_x);
	//m_size = 20;
	if ( m_x > 250)
	{
		m_Vx = - m_Vx;
		
	}
	if (m_x < -250)
	{
		m_Vx = -m_Vx;
		
	}
	if (m_y > 250)
	{
		m_Vy = -m_Vy;
		
	}
	if (m_y < -250)
	{
		m_Vy = -m_Vy;
		
	}
	
}