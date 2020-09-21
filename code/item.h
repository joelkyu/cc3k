#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include "potiontypeenum.h"
#include "goldtypeenum.h"

class Item : public Entity
{
protected:
	int value;

	Item(char);

public:
	virtual ~Item() = 0;
	int getValue();
};

#endif

