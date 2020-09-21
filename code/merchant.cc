#include "merchant.h"
#include <cmath>

Merchant::Merchant(int x, int y) : Enemy('M', x, y)
{
	maxHP = 30;
	currHP = 30;
	atk = 70;
	def = 5;
	race = Race::Merchant;
}

Merchant::~Merchant() {}

void Merchant::attack(Player& player) {
	if (!isHostile) {
		return;
	}
	else {
		
		bool canAttack = rand() % 2;

		if (canAttack) player.attackedBy(*this);
	}
}

void Merchant::attackedBy(Player& player) {
	double calculateDmg = (100.00 / (100.00 + getDef())) * player.getAtk();
	int damage = (int)ceil(calculateDmg);
	int newHP = getCurrHP() - damage;
	if (newHP <= 0) {
		newHP = 0;
		setCurrHP(newHP);
		dropGold(player);

	}
	else {
		setCurrHP(newHP);
	}
	isHostile = true;
}

void Merchant::dropGold(Player& player) {
	// drop merchant gold, only picked up if player walks over it
	shared_ptr<Gold> m = make_shared<Gold>(GoldType::MerchantHoard);
	//Cell* pos = Cell(x, y);
	//pos->setGold(m);
}
