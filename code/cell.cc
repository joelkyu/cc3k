#include <memory>
#include "cell.h"
#include "entity.h"
#include "terrain.h"
#include "gold.h"

Cell::Cell(int r, int c) {
	row = r;
	col = c;
	entity = nullptr;
	terrain = nullptr;
	golds = make_shared<vector<shared_ptr<Gold>>>(0); // set to a vector of nullptr
	// the above line is wrong, but it's not priority to fix it rn
	
}

//  ========== getters ==========
shared_ptr<Entity> Cell::getEntity() { return entity; }
bool Cell::entityExists() { return (entity == nullptr) ? false : true; }
shared_ptr<Terrain> Cell::getTerrain() { return terrain; }
shared_ptr<vector<shared_ptr<Gold>>> Cell::getGold() { return golds; }
int Cell::getRow() { return row; }
int Cell::getCol() { return col; }

//  ========== setters ==========
void Cell::setEntity(shared_ptr<Entity> e) { entity = e; }
void Cell::setTerrain(shared_ptr<Terrain> t) { terrain = t; }
void Cell::setGold(shared_ptr<Gold> g) { golds->push_back(g); }



