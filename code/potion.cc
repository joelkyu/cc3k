#include "potion.h"

Potion::Potion(PotionType potionType) : Item('P'), potionType{ potionType } {

	switch (potionType) {
	case PotionType::HpUp :
		value = 10;
		break;

	case PotionType::HpDown :
		value = -10;
		break;

	case PotionType::AtkUp:
		value = 5;
		break;

	case PotionType::AtkDown:
		value = -5;
		break;

	case PotionType::DefUp:
		value = 5;
		break;

	case PotionType::DefDown:
		value = -5;
		break;
	}
}

PotionType Potion::getPotionType()
{
	return potionType;
}


