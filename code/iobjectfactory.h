#ifndef IOBJECTFACTORY_H
#define IOBJECTFACTORY_H

#include <map>
#include <cstdlib>
#include <memory>

#include "gameObject.h"

class IObjectFactory
{
protected:

	// spawns GameObject specified in factory object field "type"
	virtual shared_ptr<GameObject> spawnObject(int x, int y) = 0;

	// spawns random GameObject
	virtual shared_ptr<GameObject> randomObject(int x, int y) { return nullptr; };

public:

	virtual ~IObjectFactory() {}
};

#endif

