#include "ipotionstrategy.h"

void IPotionStrategy::enhanceEffect()
{
	HpChange += (HpChange / 2);
	AtkChange += (AtkChange / 2);
	DefChange += (DefChange / 2);
}
