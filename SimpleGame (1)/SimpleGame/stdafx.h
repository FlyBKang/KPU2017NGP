#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream>
using namespace std;
#include <tchar.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

const int MAX_OBJECTS_COUNT = 1000;
//object Type define
const int OBJECT_BULDING = 1;
const int OBJECT_CHARACTER = 2;
const int OBJECT_BULLET = 3;
const int OBJECT_ARROW = 4;