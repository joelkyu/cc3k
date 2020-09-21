#include "passage.h"

Passage::Passage() : Terrain('#') {}


bool Passage::playerCanAccess()
{
	return true;
}

bool Passage::enemyCanAccess()
{
	return false;
}
