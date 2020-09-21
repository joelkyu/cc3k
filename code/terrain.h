#ifndef TERRAIN_H
#define TERRAIN_H

#include "gameObject.h"

class Terrain : public GameObject
{
public:
	Terrain(char display);
	virtual bool playerCanAccess() { return false;  };
	virtual bool enemyCanAccess() { return false; };
	virtual ~Terrain();
	virtual bool areStairs() { return false; };
};

#endif

