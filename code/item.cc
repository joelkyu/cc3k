#include "item.h"

Item::Item(char display) : 
	Entity(display) {}

Item::~Item() {}

int Item::getValue()
{
	return value;
}

