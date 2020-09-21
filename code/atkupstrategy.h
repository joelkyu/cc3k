#ifndef ATKUPSTRAT_H
#define ATKUPSTRAT_H

#include "ipotionstrategy.h"
class AtkUpStrategy : public IPotionStrategy
{
public:
	// increase atk by 5
	void takePotion(int& Hp, int maxHp, int& Atk, int& Def) override;

	// does max( -5 atk, 0 atk ) to atk
	void removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def) override;
};

#endif

