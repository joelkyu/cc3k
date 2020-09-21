#include <memory>
#include "display.h"

Display::Display(int row, int col)
{
	// 2D vector of row x col, filled with ' '
	displayTiles.resize(row, vector<char>(col, ' '));

	ROW_DIMENSION = row;
	COL_DIMENSION = col;
}

void Display::update(vector<vector<shared_ptr<Cell>>> cells)
{
	for (auto r = 0; r < ROW_DIMENSION; ++r) {
		for (auto c = 0; c < COL_DIMENSION; ++c) {
			updateCell(cells[r][c], r, c);
		}
	}
}

void Display::updateCell(shared_ptr<Cell> cell, int row, int col) {
	shared_ptr<Entity> entity = cell->getEntity();
	shared_ptr<Terrain> terrain = cell->getTerrain();
	shared_ptr<vector<shared_ptr<Gold>>> goldVector = cell->getGold();

	if (entity) {
		displayTiles[row][col] = entity->getDisplay();
	}
	else if (!goldVector->empty()) {
		displayTiles[row][col] = goldVector->front()->getDisplay();
	}
	else if (terrain) {
		displayTiles[row][col] = terrain->getDisplay();
	}
	else {
		displayTiles[row][col] = ' ';
	}
}

ostream& operator<<(ostream& out, const Display& td)
{
	for (auto& row : td.displayTiles) {
		for (auto& col : row) {
			out << col;
		}
		out << endl;
	}
	return out;
}
