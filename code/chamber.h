#ifndef CHAMBER_H
#define CHAMBER_H
#include <vector>

using namespace std;

class Chamber {
private:
	vector<vector<bool>> chamberMap;

public:
	// ========== big 5 ==========
	Chamber(int row, int col); // intializes to a vector of vector of false

	// ========== getters ==========
	bool getChamberValue(int row, int col);
	int getNumOfTiles();

	// ========== setters ==========
	void setChamberValue(int row, int col); // sets the value to true

	void printMap();
};

#endif // !CHAMBER_H

