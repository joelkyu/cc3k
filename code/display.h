#ifndef DISPLAY_H
#define DISPLAY_H
#include <vector>
#include <iostream>
#include <memory>

#include "cell.h"

using namespace std;

class  Cell;

class Display {
	
	// 2D vector of chars to print
	vector<vector<char>> displayTiles;
	int ROW_DIMENSION;
	int COL_DIMENSION;

	void updateCell(shared_ptr<Cell> cell, int row, int col);

public:
	Display(int row, int col); // use the constant numbers from the floor.h file. I left it like this to let it be flexible
	
	void update(vector<vector<shared_ptr<Cell>>> cells); // will update the display for all the cells in the floor

	friend ostream &operator<<(ostream& out, const Display& td);
};

ostream& operator<<(ostream& out, const Display& td);

#endif

