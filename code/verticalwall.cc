#include "verticalwall.h"

VerticalWall::VerticalWall() : Terrain('|') {}

bool VerticalWall::playerCanAccess()
{
	return false;
}

bool VerticalWall::enemyCanAccess()
{
	return false;
}
