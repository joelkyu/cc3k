#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <iostream>
#include <memory>
#include "dragongold.h"
#include "creature.h"
#include "ipotionstrategy.h"
#include <cmath>

class Enemy;

class Player : public Creature {	
protected:
	shared_ptr<Enemy> enemy;
	int gold = 0;
	int score = 0;
	vector<shared_ptr<IPotionStrategy>> potionEffects;

	Player(int x, int y);

public:

	virtual ~Player() = 0;
	int getGold();
	void setGold(int val);
	virtual int getScore();
	void setScore(int val);
	virtual void takePotion(shared_ptr<IPotionStrategy> thePotion);
	void removePotionEffects();
	virtual void attack(Enemy& enemy);
	virtual void attackedBy(Enemy& enemy);
	void pickUpGold(shared_ptr<Gold> gold);
	void death() override;
};

#endif
