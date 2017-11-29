#pragma once

#include "Player.h"
#include "Object.h"

typedef struct Client_Key
{
	bool up;
	bool down;
	bool left;
	bool right;
}Key;

struct SendToServer
{
	Key key;
};