#pragma once
#include "iobjectfactory.h"
class TerrainFactory : public IObjectFactory
{
	// . empty chamber tile, + door, # passage
	// - horizontal wall, | vertical wall
	char type;

public:
	shared_ptr<GameObject> spawnObject(int x, int y) override;

	TerrainFactory(char);
	
	// . empty chamber tile, + door, # passage
	// - horizontal wall, | vertical wall
	void setTerrainMade(char);
};

