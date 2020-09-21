#include "hpdownstrategy.h"

void HpDownStrategy::takePotion(int& Hp, int maxHp, int& Atk, int& Def)
{
	Hp = max(Hp - HpChange, 0);
}

void HpDownStrategy::removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def)
{
	// does nothing
}
