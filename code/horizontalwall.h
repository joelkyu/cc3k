#ifndef HORIZONTALWALL_H
#define HORIZONTALWALL_H

#include "terrain.h"
class HorizontalWall : public Terrain
{
public:
	HorizontalWall();
	~HorizontalWall() {}
	bool playerCanAccess() override;
	bool enemyCanAccess() override;
};

#endif

