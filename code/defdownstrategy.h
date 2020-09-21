#ifndef DEFDOWNSTRAT_H
#define DEFDOWNSTRAT_H

#include "ipotionstrategy.h"
class DefDownStrategy : public IPotionStrategy
{
public:
	// does max( -5 def, 0 def ) to def
	void takePotion(int& Hp, int maxHp, int& Atk, int& Def) override;

	// increase def by 5
	void removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def) override;
};

#endif

