#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
#include "entity.h"
#include "terrain.h"
#include "gold.h"

using namespace std;

class Cell {
private:
	
	// position on the floor
	int row;
	int col;

	// things that the cell contains
	shared_ptr<Entity> entity;
	shared_ptr<Terrain> terrain;
	shared_ptr<vector<shared_ptr<Gold>>> golds;

public:
	/*
	row and col set to position in floor
	entity set to nullptr
	terrian set to nullptr
	golds set to a vector of nullptr
	*/
	Cell(int r, int c);

	//  ========== getters ========== // return a nullptr if it is empty, feel free to change as you see fit
	shared_ptr<Entity> getEntity();
	bool entityExists();
	shared_ptr<Terrain> getTerrain();
	shared_ptr<vector<shared_ptr<Gold>>> getGold(); // maybe we will just let the other methods to mutate the array, that will be easier
	int getRow();
	int getCol();

	//  ========== setters ========== // utilized as part of the move function, maybe do the checks for collison here?, feel free to change as you see fit
	void setEntity(shared_ptr<Entity> e);
	void setTerrain(shared_ptr<Terrain> t);
	void setGold(shared_ptr<Gold> g);
};

#endif // !CELL_H
