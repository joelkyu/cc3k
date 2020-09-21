#ifndef ORC_H
#define ORC_H

#include "enemy.h"

class Orc : public Enemy {
	shared_ptr<Player> player;
public:
	Orc(int x, int y);
	~Orc();
	void attack(Player& player) override;
	void attackedBy(Player& player) override;
	void dropGold(Player& player) override;

};

#endif

