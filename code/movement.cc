#include "movement.h"

#include <cmath>
#include <ctime>


Movement::Movement(Direction direction) :
	direction{ direction } {}


void Movement::setDirection(Direction setDir)
{
	direction = setDir;
}


bool Movement::moveInDirection(shared_ptr<Entity> entity, Floor& theFloor)
{
	// check if validmove
	if (!isValidMove(entity, theFloor)) return false;

	auto creature = dynamic_pointer_cast<Creature>(entity);

	int newRow;
	int newCol;

	switch (direction) {
	case Direction::North :
		newRow = creature->getX() - 1;
		newCol = creature->getY();
		break;

	case Direction::Northeast :
		newRow = creature->getX() - 1;
		newCol = creature->getY() + 1;
		break;

	case Direction::East :
		newRow = creature->getX();
		newCol = creature->getY() + 1;
		break;

	case Direction::Southeast :
		newRow = creature->getX() + 1;
		newCol = creature->getY() + 1;
		break;

	case Direction::South :
		newRow = creature->getX() + 1;
		newCol = creature->getY();
		break;

	case Direction::Southwest :
		newRow = creature->getX() + 1;
		newCol = creature->getY() - 1;
		break;

	case Direction::West :
		newRow = creature->getX();
		newCol = creature->getY() - 1;
		break;

	case Direction::Northwest :
		newRow = creature->getX() - 1;
		newCol = creature->getY() - 1;
		break;

	case Direction::Null :
		return false;
		break;
	}

	theFloor.setCellsEntity(creature->getX(), creature->getY(), nullptr);
	theFloor.setCellsEntity(newRow, newCol, creature);

	creature->setCoords(newRow, newCol);
	
	if (creature->getRace() == Race::Troll) {
		int newHP = creature->getCurrHP() + 5;
		if (newHP >= creature->getMaxHP()) {
			creature->setCurrHP(creature->getMaxHP());
		}
		else {
			creature->setCurrHP(newHP);
		}
	}

	// pick up gold
	auto goldVector = theFloor.getGoldVector(newRow, newCol);
	if (!goldVector->empty()) {
		auto testPlayer = dynamic_pointer_cast<Player>(creature);
		if (testPlayer) {
			
			for (auto gold : *goldVector) {
				testPlayer->pickUpGold(gold);
			}
			goldVector->clear();
		}
	}

	return theFloor.cellAreStairs(newRow, newCol);
}

void Movement::randomMove(shared_ptr<Entity> entity, Floor& theFloor)
{

	auto enemy = dynamic_pointer_cast<Enemy>(entity);	// only move if enemy
	if (enemy == nullptr) return;	// dynamic cast failed

	if (enemy->getHasMoved()) return;		// enemy has already moved
	enemy->setHasMoved(true);

	do {
		int pickDirection = rand() % 9;

		if (!enemiesCanMove) {	// enemies cannot move
			pickDirection = 8;
		}

		switch (pickDirection) {
		case 0:
			direction = Direction::North;
			break;

		case 1:
			direction = Direction::Northeast;
			break;

		case 2:
			direction = Direction::East;
			break;

		case 3:
			direction = Direction::Southeast;
			break;

		case 4:
			direction = Direction::South;
			break;

		case 5:
			direction = Direction::Southwest;
			break;

		case 6:
			direction = Direction::West;
			break;

		case 7:
			direction = Direction::Northwest;
			break;

		case 8:
			direction = Direction::Null;
			break;
		}

	} while (!isValidMove(enemy, theFloor));

	moveInDirection(enemy, theFloor);
}

bool Movement::isValidMove(shared_ptr<Entity> entity, Floor& theFloor)
{
	auto creature = dynamic_pointer_cast<Creature>(entity);
	if (creature == nullptr) return false;	// dynamic cast failed

	int newRow;
	int newCol;

	switch (direction) {
	case Direction::North:
		newRow = creature->getX() - 1;
		newCol = creature->getY();
		break;

	case Direction::Northeast:
		newRow = creature->getX() - 1;
		newCol = creature->getY() + 1;
		break;

	case Direction::East:
		newRow = creature->getX();
		newCol = creature->getY() + 1;
		break;

	case Direction::Southeast:
		newRow = creature->getX() + 1;
		newCol = creature->getY() + 1;
		break;

	case Direction::South:
		newRow = creature->getX() + 1;
		newCol = creature->getY();
		break;

	case Direction::Southwest:
		newRow = creature->getX() + 1;
		newCol = creature->getY() - 1;
		break;

	case Direction::West:
		newRow = creature->getX();
		newCol = creature->getY() - 1;
		break;

	case Direction::Northwest:
		newRow = creature->getX() - 1;
		newCol = creature->getY() - 1;
		break;

	case Direction::Null:
		return true;
		break;
	}

	// check out of bouds
	if (newRow < 0 || newRow >= theFloor.getROWDIMENSION() ||
		newCol < 0 || newCol >= theFloor.getCOLDIMENSION()) {
		return false;
	}

	// check if entity already occupies cell
	if (theFloor.cellsEntityExists(newRow, newCol)) return false;

	auto testEnemyCast = dynamic_pointer_cast<Enemy>(creature);
	auto testPlayerCast = dynamic_pointer_cast<Player>(creature);

	// checking access
	if (testPlayerCast) return theFloor.playerCanAccessCell(newRow, newCol);
	if (testEnemyCast) return theFloor.enemyCanAccessCell(newRow, newCol);

	return false;
}

void Movement::pickUpPotion(Player& player, Floor& theFloor)
{
	int potionRow;
	int potionCol;

	switch (direction) {
	case Direction::North:
		potionRow = player.getX() - 1;
		potionCol = player.getY();
		break;

	case Direction::Northeast:
		potionRow = player.getX() - 1;
		potionCol = player.getY() + 1;
		break;

	case Direction::East:
		potionRow = player.getX();
		potionCol = player.getY() + 1;
		break;

	case Direction::Southeast:
		potionRow = player.getX() + 1;
		potionCol = player.getY() + 1;
		break;

	case Direction::South:
		potionRow = player.getX() + 1;
		potionCol = player.getY();
		break;

	case Direction::Southwest:
		potionRow = player.getX() + 1;
		potionCol = player.getY() - 1;
		break;

	case Direction::West:
		potionRow = player.getX();
		potionCol = player.getY() - 1;
		break;

	case Direction::Northwest:
		potionRow = player.getX() - 1;
		potionCol = player.getY() - 1;
		break;

	default :
		break;
	}

	if (theFloor.cellHasPotion(potionRow, potionCol)) {
		PotionType potionType = theFloor.getCellPotiontype(potionRow, potionCol);
		shared_ptr<IPotionStrategy> potionStrat;

		switch (potionType) {
		case PotionType::HpUp :
			potionStrat = make_shared<HpUpStrategy>();
			break;

		case PotionType::HpDown:
			potionStrat = make_shared<HpDownStrategy>();
			break;

		case PotionType::AtkUp:
			potionStrat = make_shared<AtkUpStrategy>();
			break;

		case PotionType::AtkDown:
			potionStrat = make_shared<AtkDownStrategy>();
			break;

		case PotionType::DefUp:
			potionStrat = make_shared<DefUpStrategy>();
			break;

		case PotionType::DefDown:
			potionStrat = make_shared<DefDownStrategy>();
			break;

		default :
			break;

		}
		player.takePotion(potionStrat);								// take potion
		theFloor.setCellsEntity(potionRow, potionCol, nullptr);		// remove potion taken
	}

	if (player.getRace() == Race::Troll) {
		int newHP = player.getCurrHP() + 5;
		if (newHP >= player.getMaxHP()) {
			player.setCurrHP(player.getMaxHP());
		}
		else {
			player.setCurrHP(newHP);
		}
	}

}

void Movement::toggleEnemiesCanMove()
{
	if (enemiesCanMove) {
		enemiesCanMove = false;
	}
	else {
		enemiesCanMove = true;
	}
}



