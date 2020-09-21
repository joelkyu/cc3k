#include "itemfactory.h"

#include "potion.h"
#include "dragongold.h"

shared_ptr<GameObject> ItemFactory::spawnObject(int x, int y)
{
    shared_ptr<Item> newItem;

    if (type == 'p') {              // potion
        
        newItem = make_shared<Potion>(potionType);

    }
    else {                          // gold

        newItem = make_shared<Gold>(goldType);
        
        if (goldType == GoldType::DragonHoard) {
            newItem = make_shared<DragonGold>();
        }
    }

    return newItem;
}

shared_ptr<GameObject> ItemFactory::randomObject(int x, int y)
{
    // random number between 0 and totalProbability (6 or 8)
    
    int totalProbability = (type == 'p') ? numPotionTypes : totalGoldProbability;
    int probabilityIndex = rand() % totalProbability;

    int sum = 0;
    auto potionItr = potionMap.begin();
    auto goldItr = goldMap.begin();

    // find the object to make
    while (sum < probabilityIndex) {
        if (type == 'p') {
            sum += potionItr->second;
            ++potionItr;
        }
        else {
            sum += goldItr->second;
            ++goldItr;
        }
    }

    potionType = potionItr->first;
    goldType = goldItr->first;

    // make item
	return spawnObject(x, y);
}

ItemFactory::ItemFactory(char type) : type{ type } {}

void ItemFactory::setItemType(char newType)
{
    type = newType;
}

void ItemFactory::setGoldType(GoldType setType)
{
    goldType = setType;
    type = 'g';
}

void ItemFactory::setPotionType(PotionType setType)
{
    potionType = setType;
    type = 'p';
}

