#pragma once
class Object
{

	float X, Y;
	float Vx, Vy;

public:
	Object();
	Object(float x, float y, float vx, float vy);
	~Object();

	void Update();

};

