#include "player.h"

class Enemy;

class Shade : public Player {
	shared_ptr<Enemy> enemy;
public:
	Shade(int x, int y);
	~Shade();
	void attack(Enemy& enemy) override;
	void attackedBy(Enemy& enemy) override;
	int getScore() override;
};
