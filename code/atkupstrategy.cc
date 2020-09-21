#include "atkupstrategy.h"

void AtkUpStrategy::takePotion(int& Hp, int maxHp, int& Atk, int& Def)
{
	Atk += AtkChange;
}

void AtkUpStrategy::removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def)
{
	Atk = max(Atk - AtkChange, 0);
}
