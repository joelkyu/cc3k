#include "enemyfactory.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "halfling.h"
#include "dragon.h"

EnemyFactory::EnemyFactory(Race race) : race{ race } {}

void EnemyFactory::setRaceMade(Race newRace)
{
    race = newRace;
}


shared_ptr<GameObject> EnemyFactory::spawnObject(int x, int y)
{
    shared_ptr<Enemy> newEnemy;

    switch (race) {
    case Race::Human :
        newEnemy = make_shared<Human>(x, y);
        break;

    case Race::Dwarf :
        newEnemy = make_shared<Dwarf>(x, y);
        break;

    case Race::Elf :
        newEnemy = make_shared<Elf>(x, y);
        break;

    case Race::Orc :
        newEnemy = make_shared<Orc>(x, y);
        break;

    case Race::Merchant :
        newEnemy = make_shared<Merchant>(x, y);
        break;

    case Race::Halfling :
        newEnemy = make_shared<Halfling>(x, y);
        break;

    case Race::Dragon :
        newEnemy = make_shared<Dragon>(x, y, 0, 0);    // must set coords with
        break;                                      // Dragon::setHoardCoords(int, int)

    default:
        break;
    }
    return newEnemy;
}

shared_ptr<GameObject> EnemyFactory::randomObject(int x, int y)
{
    

    // choose number from 0 to 17
    int probabilityIndex = rand() % totalProbability;

    int sum = 0;
    auto mapItr = probabilityMap.begin();

    // find enemy
    while (sum < probabilityIndex) {
        sum += mapItr->second;
        ++mapItr;
    }

    // type of enemy to create
    race = mapItr->first;

    // make object
    return spawnObject(x, y);
}
