#include "player.h"

class Enemy;

class Drow : public Player {
	shared_ptr<Enemy> enemy;
public:
	Drow(int x, int y);
	~Drow();
	void attack(Enemy& enemy) override;
	void attackedBy(Enemy& enemy) override;

	void takePotion(shared_ptr<IPotionStrategy> thePotion) override;
};
