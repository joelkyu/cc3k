#include "defupstrategy.h"

void DefUpStrategy::takePotion(int& Hp, int maxHp, int& Atk, int& Def)
{
	Def += DefChange;
}

void DefUpStrategy::removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def)
{
	Def = max(Def - DefChange, 0);
}
