#ifndef POTIONITEM_H
#define POTIONITEM_H

#include "item.h"

class Potion : public Item
{
	PotionType potionType;

public:
	Potion(PotionType);
	~Potion() {}
	PotionType getPotionType();
};

#endif

