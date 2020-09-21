#ifndef DEFUPSTRAT_H
#define DEFUPSTRAT_H

#include "ipotionstrategy.h"
class DefUpStrategy : public IPotionStrategy
{
public:
	// increase def by 5
	void takePotion(int& Hp, int maxHp, int& Atk, int& Def) override;

	// does max( -5 def, 0 def) to def
	void removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def) override;
};

#endif

