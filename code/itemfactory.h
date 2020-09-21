#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "iobjectfactory.h"
#include "potiontypeenum.h"
#include "goldtypeenum.h"

class ItemFactory : public IObjectFactory
{
	// p for potion, g for gold
	char type;
	PotionType potionType = PotionType::HpUp;	// default value
	GoldType goldType = GoldType::Small;		// default value

	// values for potion probabilities
	int numPotionTypes = 6;
	map<PotionType, int> potionMap{
		{PotionType::HpUp, 0},
		{PotionType::HpDown, 1},
		{PotionType::AtkUp, 2},
		{PotionType::AtkDown, 3},
		{PotionType::DefUp, 4},
		{PotionType::DefDown, 5}
	};

	// gold probabilities
	int totalGoldProbability = 8;
	map<GoldType, int> goldMap{
		{GoldType::Small, 5},
		{GoldType::Normal, 2},
		{GoldType::DragonHoard, 1}
	};
	
public:
	// spawns a potion if type = p, gold if type = g
	shared_ptr<GameObject> spawnObject(int x, int y) override;

	// spawns random potion or gold depending on "type" field
	shared_ptr<GameObject> randomObject(int x, int y) override;

	ItemFactory(char);

	// p for potion, g for gold
	void setItemType(char);
	void setGoldType(GoldType);
	void setPotionType(PotionType);
};

#endif

