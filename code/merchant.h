#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"

class Gold;
class Cell;

class Merchant : public Enemy {
	shared_ptr<Player> player;
	static bool isHostile;
public:
	Merchant(int x, int y);
	~Merchant();
	void attack(Player& player) override;
	void attackedBy(Player& player) override;
	void dropGold(Player& player) override;
};

#endif

