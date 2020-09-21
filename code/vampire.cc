#include "vampire.h"
#include "enemy.h"
#include <cmath>
#include <iostream>
#include <climits>


Vampire::Vampire(int x, int y) : Player(x, y) {
	maxHP = INT_MAX;
	currHP = 50;
	atk = 25;
	def = 25;
	race = Race::Vampire;
}

Vampire::~Vampire() {}

void Vampire::attack(Enemy& enemy) {
	enemy.attackedBy(*this);
	if (enemy.getRace() == Race::Dwarf) {
		setCurrHP(getCurrHP() - 5);
	}
	else {
		setCurrHP(getCurrHP() + 5);
	}
}

void Vampire::attackedBy(Enemy& enemy) {
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
}
