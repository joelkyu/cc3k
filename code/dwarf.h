#include "enemy.h"

class Player;

class Dwarf : public Enemy {
public:
	Dwarf(int x, int y);
	~Dwarf();
	void attack(Player& player) override;
	void attackedBy(Player& player) override;
	void dropGold(Player& player) override;
};
