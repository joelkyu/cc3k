#ifndef POTIONSTRATEGY_H
#define POTIONSTRATEGY_H

#include <algorithm> // for min max functions

using namespace std;

class IPotionStrategy
{
protected:
	int HpChange = 10;
	int AtkChange = 5;
	int DefChange = 5;

public:
	virtual void takePotion(int& Hp, int maxHp, int& Atk, int& Def) = 0;
	virtual void removePotionEffects(int& Hp, int maxHp, int& Atk, int& Def) = 0;

	void enhanceEffect();

	virtual ~IPotionStrategy() {}
};

#endif

