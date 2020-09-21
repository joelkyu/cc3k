#include "human.h"
#include <cmath>

Human::Human(int x, int y) : Enemy('H', x, y)
{
	maxHP = 140;
	currHP = 140;
	atk = 20;
	def = 20;
	race = Race::Human;
}

Human::~Human() {}

void Human::attack(Player& player) {
	
	bool canAttack = rand() % 2;

	if (canAttack) player.attackedBy(*this);
}

void Human::attackedBy(Player& player) {
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
}

void Human::dropGold(Player& player) {
	// drop 2 piles in cell where human died
	//int x_gold = getX();
	//int y_gold = getY();
	shared_ptr<Gold> human_gold_1 = make_shared<Gold>(GoldType::Normal);
	shared_ptr<Gold> human_gold_2 = make_shared<Gold>(GoldType::Normal);

	/*
	Cell* gold_dest_1 = getEntity;
	gold_dest_1->setGold(human_gold_1);
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; i <= 1; j++) {
			Cell* gold_dest_2 = new Cell(x_gold + i, y_gold + j);
			if (gold_dest_2->entityExists && gold_dest_2->getEntity() == ".") {
				gold_dest_2->setGold(human_gold_2);
				break;
			}
		}
	}
	*/

}

