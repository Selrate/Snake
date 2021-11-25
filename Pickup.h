#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h> 
#include <time.h>
#include <list>
#include <algorithm>


#include "Utils.h"

using namespace std;


class Pickup
{
public:
	Pickup(Utils* _utils);
	void NewPosition(list<COORD>);

	COORD GetPosition() { return Position; }
private:
	COORD Position;
	Utils* MainUtils;
};

