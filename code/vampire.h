#include "player.h"

class Enemy;

class Vampire : public Player {
	shared_ptr<Enemy> enemy;
public:
	Vampire(int x, int y);
	~Vampire();
	void attack(Enemy& enemy) override;
	void attackedBy(Enemy& enemy) override;
};
