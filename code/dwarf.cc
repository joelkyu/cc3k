#include "dwarf.h"
#include "player.h"
#include <cmath>


Dwarf::Dwarf(int x, int y) : Enemy('W', x, y)
{
	maxHP = 100;
	currHP = 100;
	atk = 20;
	def = 30;
	race = Race::Dwarf;
}


Dwarf::~Dwarf() {}

void Dwarf::attack(Player& player) {
	
	bool canAttack = rand() % 2;

	if (canAttack) player.attackedBy(*this);
}

void Dwarf::attackedBy(Player& player) {
	double calculateDmg = (100.00 / (100.00 + getDef())) * player.getAtk();
	int damage = (int)ceil(calculateDmg);
	int newHP = getCurrHP() - damage;
	if (newHP <= 0) {
		newHP = 0;
		setCurrHP(newHP);
		//enemy has been killed
		//call death function?
		//call dropGold function
	}
	else {
		setCurrHP(newHP);
	}
}

void Dwarf::dropGold(Player& player) {
	int gold = 0;
	int goldRandom = rand() % 2 + 1;
	if (goldRandom == 1) {
		gold = 1;
	}
	else {
		gold = 2;
	}
	player.setGold(player.getGold() + gold);
}


