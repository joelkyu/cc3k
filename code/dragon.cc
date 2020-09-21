#include "dragon.h"

Dragon::Dragon(int x, int y, int hoard_x, int hoard_y) : 
	Enemy('D', x, y), hoardLocationX{ hoard_x }, hoardLocationY{ hoard_y }
{
	maxHP = 150;
	currHP = 150;
	atk = 20;
	def = 20;
	race = Race::Dragon;
}

Dragon::~Dragon() {}

int Dragon::getHoardCoordsX() {
	return hoardLocationX;
}
int Dragon::getHoardCoordsY() {
	return hoardLocationY;
}

void Dragon::setHoardCoords(int x, int y)
{
	hoardLocationX = x;
	hoardLocationY = y;
}
/*
void Dragon::attack(Player& player) {

}
void Dragon::attackedBy(Player& player) {

}
*/

