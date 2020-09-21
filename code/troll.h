#include "player.h"

class Enemy;

class Troll : public Player {
	shared_ptr<Enemy> enemy;
public:
	Troll(int x, int y);
	~Troll();
	void attack(Enemy& enemy) override;
	void attackedBy(Enemy& enemy) override;
};

