#ifndef EMPTYCHAMBERTILE_H
#define EMPTYCHAMBERTILE_H

#include "terrain.h"
class EmptyChamberTile : public Terrain
{
public:
	EmptyChamberTile();
	~EmptyChamberTile() {}
	bool playerCanAccess() override;
	bool enemyCanAccess() override;
};

#endif

