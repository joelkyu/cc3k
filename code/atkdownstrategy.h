#ifndef ATKDOWNSTRAT_H
#define ATKDOWNSTRAT_H

#include "ipotionstrategy.h"
class AtkDownStrategy : public IPotionStrategy
{
public:
	// does max( -5 atk, 0 atk ) to atk
	void takePotion(int& Hp, int maxHp, int& Atk, int& Def) override;

	// increase atk by 5
	void removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def) override;
};

#endif

