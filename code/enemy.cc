#include "enemy.h"

Enemy::Enemy(char display, int x, int y) : Creature(display, x, y) {}

Enemy::~Enemy() {}

bool Enemy::getHasMoved() {
	return hasMoved;
}

void Enemy::setHasMoved(bool moved) {
	hasMoved = moved;
}

void Enemy::attack(Player& player) {}

void Enemy::attackedBy(Player& player) {}

void Enemy::dropGold(Player& player) {

}

void Enemy::move() {
}

void Enemy::death() {

}

