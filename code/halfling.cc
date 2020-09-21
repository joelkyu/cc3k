#include "halfling.h"


Halfling::Halfling(int x, int y) : Enemy('L', x, y)
{
	maxHP = 100;
	currHP = 100;
	atk = 15;
	def = 20;
	race = Race::Halfling;
}

Halfling::~Halfling() {}

void Halfling::attack(Player& player) {
	
	bool canAttack = rand() % 2;

	if (canAttack) player.attackedBy(*this);
}
void Halfling::attackedBy(Player& player) {
	
	bool isAttacked = rand() % 2;

	double calculateDmg = (100.00 / (100.00 + getDef())) * player.getAtk();
	int damage = isAttacked ? (int)ceil(calculateDmg) : 0;

	int newHP = getCurrHP() - damage;
	if (newHP <= 0) {
		newHP = 0;
		setCurrHP(newHP);
		//enemy has been killed
		//call death function?
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
	else {
		setCurrHP(newHP);
	}

}

