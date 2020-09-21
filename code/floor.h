#ifndef FLOOR_H
#define FLOOR_H

#include "chamber.h"
#include "display.h"
#include "attack.h"
#include "player.h"
#include "potion.h"

#include "playerfactory.h"
#include "itemfactory.h"
#include "terrainfactory.h"
#include "enemyfactory.h"

#include <vector>
#include <memory>
#include <fstream>
#include <istream>
#include <sstream>

class Movement;

using namespace std;

class Floor {

	// map dimensions
	const int ROW_DIMENSION = 25;
	const int COL_DIMENSION = 79;

	// floor level
	int floorLevel;

	// movement class and dummy direction
	shared_ptr<Movement> movement;
	// Attack class with dummy direction
	shared_ptr<Attack> attack;
	

	// Specify the player's chosen race to help with spawning player
	PlayerRace PLAYER_RACE;

	// pointer to player
	shared_ptr<Player> THE_PLAYER;
	
	// display class has 2D vector of chars
	shared_ptr<Display> display;

	// Chamber has 2D vector of bools
	vector<shared_ptr<Chamber>> chambers;

	// cells contain terrain, entities, gold
	// working 2D vector
	vector<vector<shared_ptr<Cell>>> cells;

	/*
	initalizes cells to :
		- have a nullptr for its pointer fields
		- contains value for its coordinates
	*/
	void initCells(); 


	// helper function for readFloor that alters chambers field
	void setChamberVector();
	/* 
	read in a floor layout, will initialize the cells with the floor accordingly
	will fill in chambers as well
	will spawn entities that are in the map
	*/
	void readFloor(ifstream& mapFile);

	/* only called when the read in floor is empty
	   clears out all cells
	   will create a RandomSpawn object and call fillCells() on it
	   will be called by readFloor()
	*/ 
	void randomSpawn();

public:
	// ========== constructors ==========
	Floor(); 


	// ========== actual functions ============

	/* 
	initilizes the dungeon with the following conditions:
		- floorLevel set to 1
		- player race from player input
		- intializes display to 2D vector of row x col, filled with ' '
		- intializes chambers to a vector of garbage values
		- calls initCells()
		- calls readFloor() to initalize the map
		- will call spawnRandom() if isMapProvided is false
	returns:
		- true if intailization is successful
		- false if quit, or if EOD
	*/
	bool init(ifstream &mapFile, bool isMapProvided);

	/*
	reads the next floor, most likely called by the stair object
	calleds readFloor()
	manages the floorLevel
	!!! make sure to intailize the cells as nullptr
	calls the score/death method on the player if the floor level is greater than 5

	*/
	void nextFloor(ifstream& mapFile, bool isMapProvided);

	/*
	called from the main after every player action
	- calls attack for every enemy entity
	- if the hasMoved field for the enemy is false, call move for that enemy entity
	- update the display for all cells
	- sets hasMoved for all entities back to false
	*/
	void tick();



	// ========== getters ==========

	// get playerRace
	PlayerRace getPlayerRace();

	// get player pointer
	shared_ptr<Player> getPlayer();

	// get ROWDIMENSION
	int getROWDIMENSION();

	// get COLDIMENSION
	int getCOLDIMENSION();

	// get chambers;
	bool getChambers(int chamber, int x, int y);

	// turns true of Entity exists at cell with given coordinates
	bool cellsEntityExists(int x, int y);

	// returns if an enemy can occupy cell
	bool enemyCanAccessCell(int x, int y);

	// returns if player can occupy cell
	bool playerCanAccessCell(int x, int y);

	// returns if cell are stairs
	bool cellAreStairs(int x, int y);

	// returns if cell has a potion
	bool cellHasPotion(int x, int y);

	PotionType getCellPotiontype(int x, int y);

	shared_ptr<Enemy> getEnemy(int x, int y);

	int getFloor();

	shared_ptr<vector<shared_ptr<Gold>>> getGoldVector(int x, int y);

	shared_ptr<Movement> getMovement();

	// ========== setters ==========

	// sets the cell with an entity at the given coordinates
	void setCellsEntity(int x, int y, shared_ptr<Entity> entity);

	void setGold(int x, int y, GoldType gold);

	void toggleEnemyMovement();

	// ========== operator overrides ==========
	friend ostream & operator<<(ostream& out, const Floor & f);
};

ostream& operator<<(ostream& out, const Floor& f);

#endif
