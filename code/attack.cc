#include "attack.h"
#include "enemy.h"
#include "player.h"
#include "floor.h"
#include "cell.h"

Attack::Attack(Direction direction) : 
	direction{ direction } {}


void Attack::enemyAttack(shared_ptr<Entity> enemy_entity, shared_ptr<Entity> player_entity, Floor& theFloor)
{
	auto enemy = dynamic_pointer_cast<Enemy>(enemy_entity);	
	if (enemy == nullptr) return;	// dynamic cast failed

	auto player = dynamic_pointer_cast<Player>(player_entity);	
	if (player == nullptr) return;	// dynamic cast failed

	// check if enemy can attack player
	if (isValidAttack(enemy, player, theFloor)) {

		// enemy attacks player
		if (enemy->getHasMoved() != true) {
			enemy->attack(*player);
			enemy->setHasMoved(true);
		}
	}
	
}

bool Attack::isValidAttack(shared_ptr<Entity> entAttacker, shared_ptr<Entity> entVictim, Floor& theFloor)
{
	// check if both are creatures
	auto attacker = dynamic_pointer_cast<Creature>(entAttacker);
	auto victim = dynamic_pointer_cast<Creature>(entVictim);
	if (!attacker || !victim) return false;						// dynamic cast failed

	// check around attacker
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			
			// return if victim is within 1 block of attacker
			if (attacker->getX() + i == victim->getX() && 
				attacker->getY() + j == victim->getY()) {

				return true;
			}

		}
	}
	return false;
}



// helper for playerAttack that drops gold
void Attack::dropGold(Race enemyRace, int x, int y, Floor& theFloor) {
	switch (enemyRace) {

	// drop merchant hoard
	case Race::Merchant :
		theFloor.setGold(x, y, GoldType::MerchantHoard);
		break;

	// drop 2 normal piles
	case Race::Human :
		theFloor.setGold(x, y, GoldType::Normal);
		theFloor.setGold(x, y, GoldType::Normal);
		break;

	// ignore dragon for now
	default :
		break;
	}
}

void Attack::playerAttack(shared_ptr<Entity> player_entity, Floor& theFloor)
{
	auto player = dynamic_pointer_cast<Player>(player_entity);
	if (player == nullptr) return;	// dynamic cast failed

	int attackRow;
	int attackCol;

	switch (direction) {
	case Direction::North:
		attackRow = player->getX() - 1;
		attackCol = player->getY();
		break;

	case Direction::Northeast:
		attackRow = player->getX() - 1;
		attackCol = player->getY() + 1;
		break;

	case Direction::East:
		attackRow = player->getX();
		attackCol = player->getY() + 1;
		break;

	case Direction::Southeast:
		attackRow = player->getX() + 1;
		attackCol = player->getY() + 1;
		break;

	case Direction::South:
		attackRow = player->getX() + 1;
		attackCol = player->getY();
		break;

	case Direction::Southwest:
		attackRow = player->getX() + 1;
		attackCol = player->getY() - 1;
		break;

	case Direction::West:
		attackRow = player->getX();
		attackCol = player->getY() - 1;
		break;

	case Direction::Northwest:
		attackRow = player->getX() - 1;
		attackCol = player->getY() - 1;
		break;

	case Direction::Null:
		attackRow = player->getX();
		attackCol = player->getY();
		break;
	}

	if (!theFloor.cellsEntityExists(attackRow, attackCol)) return;

	auto enemy = theFloor.getEnemy(attackRow, attackCol);
	if (enemy == nullptr) return;	// dynamic cast failed


	// check if player can attack enemy
	if (isValidAttack(player, enemy, theFloor)) {

		// player attacks enemy
		player->attack(*enemy);
		// enemy is dead
		if (enemy->getCurrHP() <= 0) {
			enemy->dropGold(*player);
			dropGold(enemy->getRace(), attackRow, attackCol, theFloor);
			theFloor.setCellsEntity(attackRow, attackCol, nullptr);
		}
	}
}

void Attack::setDirection(Direction newDirection)
{
	direction = newDirection;
}



