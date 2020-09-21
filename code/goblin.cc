#include "goblin.h"
#include "enemy.h"
#include <cmath>
#include <iostream>


Goblin::Goblin(int x, int y) : Player(x, y) {
	maxHP = 110;
	currHP = 110;
	atk = 15;
	def = 20;
	race = Race::Goblin;
}

Goblin::~Goblin() {}

void Goblin::attack(Enemy& enemy) {
	enemy.attackedBy(*this);
}

void Goblin::attackedBy(Enemy& enemy) {
	double calculateDmg = (100.00 / (100.00 + getDef())) * enemy.getAtk();
	int damage;

	if (getRace() == Race::Drow) {
		damage = (int)(1.5 * ceil(calculateDmg));
	}
	else {
		damage = (int)ceil(calculateDmg);
	}
	
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


