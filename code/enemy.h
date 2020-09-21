#ifndef ENEMY_H
#define ENEMY_H
#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include "player.h"

using namespace std;


class Enemy : public Creature {
protected:
	shared_ptr<Player> player;
	bool hasMoved = false;

	Enemy(char display, int x, int y);

public:
	virtual ~Enemy() = 0;
	bool getHasMoved();
	void setHasMoved(bool moved);
	virtual void attack(Player& Player);
	virtual void attackedBy(Player& Player);
	virtual void dropGold(Player& player);
	void move() override;
	void death() override;
};

#endif


