#ifndef STAIRS_H
#define STAIRS_H

#include "terrain.h"
class Stairs : public Terrain
{
public:
	Stairs();
	bool areStairs() override;
	bool playerCanAccess() override;
	bool enemyCanAccess() override;
};

#endif

