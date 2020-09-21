#include "door.h"

Door::Door() : Terrain('+') {}

bool Door::playerCanAccess()
{
	return true;
}

bool Door::enemyCanAccess()
{
	return false;
}
