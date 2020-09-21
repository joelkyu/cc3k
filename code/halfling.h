#ifndef HALFLING_H
#define HALFLING_H

#include "enemy.h"

class Halfling : public Enemy {
public:
	Halfling(int x, int y);
	~Halfling();
	void attack(Player& player) override;
	void attackedBy(Player& player) override;
};

#endif

