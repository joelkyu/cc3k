#include "stairs.h"

Stairs::Stairs() : Terrain('\\') {}


bool Stairs::areStairs()
{
	return true;
}

bool Stairs::playerCanAccess()
{
	return true;
}

bool Stairs::enemyCanAccess()
{
	return false;
}

