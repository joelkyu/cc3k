#ifndef DOOR_H
#define DOOR_H

#include "terrain.h"
class Door : public Terrain
{
public:
	Door();
	~Door() {}
	bool playerCanAccess() override;
	bool enemyCanAccess() override;
};

#endif

