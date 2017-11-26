
#include "stdafx.h"
#include "Player.h"
Player::Player(){}
Player::Player(int n,float x, float y, float r, float g, float b)
{
	num = n;
	X = x;
	Y = y;
	R = r;
	G = g;
	B = b;
}
//	 void Player::Update(bool up, bool down, bool left, bool right)
//	 {
//	 	if (up)
//	 	{
//	 		Y =+ 1.0f;
//	 	}
//	 	if (down)
//	 	{
//	 		Y =- 1.0f;
//	 	}
//	 	if (left)
//	 	{
//	 		X =- 1.0f;
//	 	}
//	 	if (right)
//	 	{
//	 		X =+ 1.0f;
//	 	}
//	 }
Player::~Player()
{
}
