#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "iobjectfactory.h"
#include "raceenum.h"

class EnemyFactory : public IObjectFactory
{
	// default
	Race race = Race::Human;

	// probabilities
	int totalProbability = 18;
	map<Race, int> probabilityMap {
		{Race::Human , 4},
		{Race::Dwarf, 3},
		{Race::Elf, 2},
		{Race::Orc, 2},
		{Race::Merchant, 2},
		{Race::Halfling, 5}
	};

public:
	EnemyFactory(Race);
	void setRaceMade(Race);
	shared_ptr<GameObject> spawnObject(int x, int y) override;
	shared_ptr<GameObject> randomObject(int x, int y) override;
};

#endif

