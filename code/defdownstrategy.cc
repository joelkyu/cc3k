#include "defdownstrategy.h"

void DefDownStrategy::takePotion(int& Hp, int maxHp, int& Atk, int& Def)
{
	Def = max(Def - 5, 0);
}

void DefDownStrategy::removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def)
{
	Def += DefChange;
}
