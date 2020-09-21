#include "hpupstrategy.h"

void HpUpStrategy::takePotion(int& Hp, int maxHp, int& Atk, int& Def)
{
	Hp = min(Hp + HpChange, maxHp);
}

void HpUpStrategy::removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def)
{
	// does nothing
}
