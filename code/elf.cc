#include "elf.h"
#include <cmath>

Elf::Elf(int x, int y) : Enemy('E', x, y)
{
	maxHP = 140;
	currHP = 140;
	atk = 30;
	def = 10;
	race = Race::Elf;
}

Elf::~Elf() {}

void Elf::attack(Player& player) {
	int i = 0;
	if (player.getRace() == Race::Drow) {
		i = 1;
	}

	for (; i <= 1; i++) {
		
		bool canAttack = rand() % 2;

		if (canAttack) player.attackedBy(*this);
	}
}

void Elf::attackedBy(Player& player) {
	double calculateDmg = (100.00 / (100.00 + getDef())) * player.getAtk();
	int damage = (int)ceil(calculateDmg);
	int newHP = getCurrHP() - damage;
	if (newHP <= 0) {
		newHP = 0;
		setCurrHP(newHP);
		//enemy has been killed
		//call death function?
		int goldDrop = rand() % 2 + 1;
		if (goldDrop == 1) {
			player.setGold(player.getGold() + goldDrop);
		}
		else {
			player.setGold(player.getGold() + goldDrop);
		}
	}
	else {
		setCurrHP(newHP);
	}
}

