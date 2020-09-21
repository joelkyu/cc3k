#include "shade.h"
#include "enemy.h"
#include <cmath>


Shade::Shade(int x, int y) : Player(x, y) {
	maxHP = 125;
	currHP = 125;
	atk = 25;
	def = 25;
	race = Race::Shade;
}

Shade::~Shade() {}

void Shade::attack(Enemy& enemy) {
	enemy.attackedBy(*this);
}

void Shade::attackedBy(Enemy& enemy) {
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

int Shade::getScore()
{
	gold += (gold / 2);
	return gold;
}
