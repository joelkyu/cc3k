#include "horizontalwall.h"

HorizontalWall::HorizontalWall() : Terrain('-') {}

bool HorizontalWall::playerCanAccess()
{
	return false;
}

bool HorizontalWall::enemyCanAccess()
{
	return false;
}
