#include "player.h"

class Enemy;

class Goblin : public Player {
	shared_ptr<Enemy> enemy;
public:
	Goblin(int x, int y);
	~Goblin();
	void attack(Enemy& enemy) override;
	void attackedBy(Enemy& enemy) override;
};
