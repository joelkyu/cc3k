#ifndef CREATURE_H
#define CREATURE_H
#include <vector>
#include <iostream>
#include <string>
#include "entity.h"
#include "raceenum.h"

using namespace std;

class Creature : public Entity {
protected:
	int currHP;
	int maxHP;
	int atk;
	int def;
	Race race;

	int coordsX;
	int coordsY;

	Creature(char display, int x, int y);

public:
	
	virtual ~Creature() = 0;

	int& getCurrHP();
	int getMaxHP();
	int& getAtk();
	int& getDef();
	Race getRace();

	void setCurrHP(int val);
	void setMaxHP(int val);
	void setAtk(int val);
	void setDef(int val);

	void setCoords(int x, int y);
	int getX();
	int getY();

	virtual void move();
	virtual void death();
};

#endif
