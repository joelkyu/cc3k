#include "playerfactory.h"

#include "drow.h"
#include "goblin.h"
#include "shade.h"
#include "troll.h"
#include "vampire.h"
#include "stairs.h"

shared_ptr<GameObject> PlayerFactory::spawnObject(int x, int y)
{
	shared_ptr<Player> newObject;

	switch (playerRace) { 
	case PlayerRace::Drow :
		newObject = make_shared<Drow>(x, y);
		break;

	case PlayerRace::Goblin :
		newObject = make_shared<Goblin>(x, y);
		break;

	case PlayerRace::Shade :
		newObject = make_shared<Shade>(x, y);
		break;

	case PlayerRace::Troll :
		newObject = make_shared<Troll>(x, y);
		break;

	case PlayerRace::Vampire :
		newObject = make_shared<Vampire>(x, y);
		break;
	}
	
	return newObject;
}

PlayerFactory::PlayerFactory(PlayerRace race) :playerRace{ race } {}



