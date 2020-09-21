#ifndef HUMAN_H
#define HUMAN_H

#include <memory>
#include "enemy.h"

class Gold;
class Cell;

class Human : public Enemy {
public:
	Human(int x, int y);
	~Human();
	void attack(Player& player) override;
	void attackedBy(Player& player) override;
	void dropGold(Player& player) override;
};

#endif

