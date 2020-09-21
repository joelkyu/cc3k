#ifndef ATTACK_H
#define ATTACK_H

#include "directionenum.h"
//#include "floor.h"
#include "enemy.h"
#include "player.h"

class Floor;

class Attack
{
	// dummy default value
	Direction direction = Direction::North;
	//Floor& theFloor;

public:
	Attack(Direction);

	// checks if player is in range of enemy, if enemy has not moved, then attack player
	// will have to do a hostile check for merchant
	// do something special for dragon 
	void enemyAttack(shared_ptr<Entity> enemy_entity, shared_ptr<Entity> player_entity, Floor&);

	bool isValidAttack(shared_ptr<Entity> enemy_entity, shared_ptr<Entity> player_entity, Floor&);


	void dropGold(Race enemyRace, int x, int y, Floor&);

	// check if there is an enemy in a direction, if so attack it
	void playerAttack(shared_ptr<Entity>, Floor&);

	// set direction
	void setDirection(Direction);

};

#endif

#pragma once
