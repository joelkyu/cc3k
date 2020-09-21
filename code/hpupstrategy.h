#ifndef HPUPSTRATEGY_H
#define HPUPSTRATEGY_H

#include "ipotionstrategy.h"

class HpUpStrategy : public IPotionStrategy
{
public:
	// does min( +10 hp, max hp) to hp
	void takePotion(int& Hp, int maxHp, int& Atk, int& Def) override;

	// does nothing
	void removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def) override;
};

#endif

