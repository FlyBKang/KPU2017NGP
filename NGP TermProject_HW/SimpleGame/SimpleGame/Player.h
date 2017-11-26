#pragma once
class Player
{
public:
	int num;
	float X, Y;
	float R, G, B;
	int life = 3;
	bool IsCollision = false;
	Player();
	Player(int n,float x, float y, float r, float g, float b);
	//void Update(bool up, bool down, bool left, bool right);
	~Player();
};

