#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"

class Dragon : public Enemy {
	int hoardLocationX;
	int hoardLocationY;
	bool isHostile = false;

public:
	Dragon(int x, int y, int hoard_x, int hoard_y);
	~Dragon();
	int getHoardCoordsX();
	int getHoardCoordsY();
	void setHoardCoords(int x, int y);
	//void attack(Player& player) override;
	//void attackedBy(Player& player) override;
};

#endif

// adding a comment to dragon
