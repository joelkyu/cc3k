#include "emptychambertile.h"

EmptyChamberTile::EmptyChamberTile() : Terrain('.') {}

bool EmptyChamberTile::playerCanAccess()
{
	return true;
}

bool EmptyChamberTile::enemyCanAccess()
{
	return true;
}
