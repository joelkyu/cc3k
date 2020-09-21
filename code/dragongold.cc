#include "dragongold.h"

DragonGold::DragonGold() : Gold(GoldType::DragonHoard) {}

/*void DragonGold::setDragon(shared_ptr<Dragon> newDragon)
{
	dragon = newDragon;
}*/

void DragonGold::killDragon()
{
	dragonIsDead = true;
}

bool DragonGold::getDragonIsDead()
{
	return dragonIsDead;
}
