#include "player.h"
#include "enemy.h"

Player::Player(int x, int y) : Creature('@', x, y) {}

Player::~Player() {}

void Player::takePotion(shared_ptr<IPotionStrategy> thePotion) {
	thePotion->takePotion(getCurrHP(), getMaxHP(), getAtk(), getDef());
	potionEffects.push_back(thePotion);
}

void Player::removePotionEffects() {
	for (auto effect : potionEffects) {
		effect->removePotionEffects(getCurrHP(), getMaxHP(), getAtk(), getDef());
	}
	potionEffects.clear();
}

int Player::getGold() {
	return gold;
}

void Player::setGold(int val) {
	gold = val;
}
int Player::getScore() {
	return gold;
}

void Player::setScore(int val) {
	score = val;
}

void Player::attack(Enemy& enemy) {
	enemy.attackedBy(*this);
}

void Player::attackedBy(Enemy& enemy) {}

void Player::pickUpGold(shared_ptr<Gold> gold) {
	//if (gold->getType() != GoldType::DragonHoard) {
		setGold(getGold() + gold->getValue());
	//}
}

void Player::death() {}
