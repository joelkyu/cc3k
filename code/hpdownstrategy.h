#ifndef HPDOWNSTRATEGY_H
#define HPDOWNSTRATEGY_H

#include "ipotionstrategy.h"

class HpDownStrategy : public IPotionStrategy
{
public:
	// does max( -10hp, 0hp ) to hp
	// Player::takePotion(int&) calls death if hp is 0
	void takePotion(int& Hp, int maxHp, int& Atk, int& Def) override;

	// does nothing
	void removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def) override;
};

#endif

