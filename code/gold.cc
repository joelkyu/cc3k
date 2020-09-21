#include "gold.h"

Gold::Gold(GoldType goldType) : Item('G'), goldType{ goldType } {

	switch (goldType) {
	case GoldType::Small :
		value = 1;
		break;

	case GoldType::Normal :
		value = 2;
		break;

	case GoldType::MerchantHoard :
		value = 4;
		break;

	case GoldType::DragonHoard :
		value = 6;
		break;
	}
}

GoldType Gold::getType()
{
	return goldType;
}

int Gold::getValue()
{
	return Item::getValue();
}

