#include "troll.h"
#include "enemy.h"
#include <cmath>
#include <iostream>


Troll::Troll(int x, int y) : Player(x, y) {
	maxHP = 120;
	currHP = 120;
	atk = 25;
	def = 15;
	race = Race::Troll;
}
Troll::~Troll() {}

void Troll::attack(Enemy& enemy) {
	// gets 5HP at the end of every turn
	enemy.attackedBy(*this);
	int newHP = getCurrHP() + 5;
	if (newHP >= getMaxHP()) {
		setCurrHP(getMaxHP());
	}
	else {
		setCurrHP(newHP);
	}
}

void Troll::attackedBy(Enemy& enemy) {
	double calculateDmg = (100.00 / (100.00 + getDef())) * enemy.getAtk();
	int damage = (int)ceil(calculateDmg);
	int newHP = getCurrHP() - damage;
	if (newHP <= 0) {
		newHP = 0;
		setCurrHP(newHP);
		//player has been killed
		//call death function?
	}
	else {
		setCurrHP(newHP);
	}

	//regain 5HP at the end of every turn if not dead
	newHP = getCurrHP() + 5;
	if (newHP >= getMaxHP()) {
		setCurrHP(getMaxHP());
	}
	else {
		setCurrHP(newHP);
	}
}

