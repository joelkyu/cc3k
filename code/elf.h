#ifndef ELF_H
#define ELF_H

#include "enemy.h"

class Elf : public Enemy {
public:
	Elf(int x, int y);
	~Elf();
	void attack(Player& player) override;
	void attackedBy(Player& player) override;
};

#endif

