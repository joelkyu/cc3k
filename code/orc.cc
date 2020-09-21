#include "orc.h"
#include <cmath>

Orc::Orc(int x, int y) : Enemy('O', x, y)
{
	maxHP = 180;
	currHP = 180;
	atk = 30;
	def = 25;
	race = Race::Orc;
}

Orc::~Orc() {}

void Orc::attack(Player& player) {
	
	bool canAttack = rand() % 2;

	if (canAttack) player.attackedBy(*this);
}

void Orc::attackedBy(Player& player) {
	double calculateDmg = (100.00 / (100.00 + getDef())) * player.getAtk();
	int damage = (int)ceil(calculateDmg);
	int newHP = getCurrHP() - damage;
	if (newHP <= 0) {
		newHP = 0;
		setCurrHP(newHP);
		//enemy has been killed
		
	}
	else {
		setCurrHP(newHP);
		//player has attacked orc
	}
}

void Orc::dropGold(Player& player) {
	int goldDrop = rand() % 2 + 1;
	if (goldDrop == 1) {
		player.setGold(player.getGold() + goldDrop);
	}
	else {
		player.setGold(player.getGold() + goldDrop);
	}
}
