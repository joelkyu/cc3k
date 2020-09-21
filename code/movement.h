#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "directionenum.h"
#include "floor.h"
#include "enemy.h"

#include "hpupstrategy.h"
#include "hpdownstrategy.h"
#include "atkupstrategy.h"
#include "atkdownstrategy.h"
#include "defupstrategy.h"
#include "defdownstrategy.h"

class Movement
{
	// dummy default value
	Direction direction = Direction::North;
	//Floor theFloor;

	// enemies can move or not
	bool enemiesCanMove = true;

public:
	Movement(Direction);

	void setDirection(Direction);

	// returns true when player moves onto stairs
	bool moveInDirection(shared_ptr<Entity>, Floor&);

	// moves creature in a random valid direction
	void randomMove(shared_ptr<Entity>, Floor&);

	// returns true if creature is free to move here
	bool isValidMove(shared_ptr<Entity>, Floor&);

	void pickUpPotion(Player&, Floor&);

	void toggleEnemiesCanMove();
};

#endif

