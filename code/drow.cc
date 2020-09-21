#include "drow.h"
#include "enemy.h"
#include <cmath>


Drow::Drow(int x, int y) : Player(x, y) {
	maxHP = 150;
	currHP = 150;
	atk = 25;
	def = 15;
	race = Race::Drow;
}

Drow::~Drow() {}

void Drow::attack(Enemy& enemy) {
	enemy.attackedBy(*this);
}

void Drow::attackedBy(Enemy& enemy) {
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

void Drow::takePotion(shared_ptr<IPotionStrategy> thePotion)
{
	thePotion->enhanceEffect();
	Player::takePotion(thePotion);
}

