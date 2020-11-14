#ifndef DRAGONGOLD_H
#define DRAGONGOLD_H

#include "gold.h"
#include <memory>

class Dragon;

class DragonGold : public Gold
{
	bool dragonIsDead = false;
	//shared_ptr<Dragon> dragon;
	
public:
	DragonGold();
	~DragonGold() {}
	void setDragon(shared_ptr<Dragon>);
	void killDragon();
	bool getDragonIsDead();
};

#endif

// adding a comment to dragongold.h
