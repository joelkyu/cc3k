#include <vector>
#include <algorithm>
#include "chamber.h"

#include <iostream>

using namespace std;

// ========== big 5 ==========
Chamber::Chamber(int row, int col)
{
	for (int i = 0; i < row; ++i) {
		vector<bool> newRow;
		for (int j = 0; j < col; ++j) {
			newRow.push_back(false);
		}
		chamberMap.push_back(newRow);
	}

}

// ========== getters ==========
bool Chamber::getChamberValue(int row, int col) { return chamberMap[row][col]; }

int Chamber::getNumOfTiles()
{
	int numTiles = 0;
	for (int row = 0; row < (int)chamberMap.size(); ++row) {
		for (int col = 0; col < (int)chamberMap[row].size(); ++col) {
			if (chamberMap[row][col] == true) {
				numTiles++;
			}
		}
	}
	//printMap();

	return numTiles;
}

// print chamberMap for debugging purposes
void Chamber::printMap() {

	for (int row = 0; row < (int)chamberMap.size(); ++row) {
		for (int col = 0; col < (int)chamberMap[row].size(); ++col) {
			
			cout << chamberMap[row][col];

		}
		cout << endl;
	}
}

// ========== setters ==========
void Chamber::setChamberValue(int row, int col) { chamberMap[row][col] = true; }


