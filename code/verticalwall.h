#ifndef VERTICALWALL_H
#define VERTICALWALL_H

#include "terrain.h"
class VerticalWall : public Terrain
{
public:
	VerticalWall();
	~VerticalWall() {}
	bool playerCanAccess() override;
	bool enemyCanAccess() override;
};

#endif

