
#include "stdafx.h"
#include "Object.h"

Object::Object(){}
Object::Object(float x, float y, float vx, float vy)
{
	X = x;
	Y = y;
	Vx = vx;
	Vy = vy;
}
Object:: ~Object(){}
void Object::Update()
{
	X += Vx;
	Y += Vy;
	if (BOUNDERY_ZONE / 2 < X)
		Vx = -Vx;
	if (-BOUNDERY_ZONE / 2 >  X)
		Vx = -Vx;
	if (BOUNDERY_ZONE / 2 < Y)
		Vy = -Vy;
	if (-BOUNDERY_ZONE / 2 >  Y)
		Vy = -Vy;
}
	