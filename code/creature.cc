#include <iostream>
#include <climits>
#include "creature.h"
using namespace std;

Creature::Creature(char display, int x, int y) : 
	Entity(display), coordsX{ x }, coordsY{ y } {}

Creature::~Creature() {}

int& Creature::getCurrHP() { return currHP; }

int Creature::getMaxHP() { return maxHP; };

int& Creature::getAtk() { return atk; };

int& Creature::getDef() { return def; }

Race Creature::getRace() { return race; }

void Creature::setCurrHP(int val) { currHP = val; }

void Creature::setMaxHP(int val) { maxHP = val; }

void Creature::setAtk(int val) { atk = val; }

void Creature::setDef(int val) { def = val; }

void Creature::setCoords(int x, int y)
{
	coordsX = x;
	coordsY = y;
}

int Creature::getX()
{
	return coordsX;
}

int Creature::getY()
{
	return coordsY;
}

void Creature::move() {}

void Creature::death() {}
