#ifndef GOLD_H
#define GOLD_H

#include "item.h"

class Gold : public Item
{
	GoldType goldType;

public:
	Gold(GoldType);
	~Gold() {}
	GoldType getType();
	int getValue();
};

#endif

