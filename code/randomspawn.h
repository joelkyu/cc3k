#ifndef SPAWNING_H
#define SPAWNING_H

#include "floor.h"
#include "iobjectfactory.h"

class SpawnCells
{
	shared_ptr<Floor> theFloor;

	// spawn 
	void fillCellsRandom();
};


#endif

