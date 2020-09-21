#include "atkdownstrategy.h"

void AtkDownStrategy::takePotion(int& Hp, int maxHp, int& Atk, int& Def)
{
	Atk = max(Atk - AtkChange, 0);
}

void AtkDownStrategy::removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def)
{
	Atk += AtkChange;
}
