#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "iobjectfactory.h"
#include "playerraceenum.h"

class PlayerFactory : public IObjectFactory
{
	// default option
	PlayerRace playerRace = PlayerRace::Shade;

public:
	// spawns a player if type = p, stairs if type = s
	shared_ptr<GameObject> spawnObject(int x, int y) override;

	// p for player, s for stairs
	// call with PlayerStairsFactory('s') or PlayerStairsFactory('p', PlayerRace)
	PlayerFactory(PlayerRace race);
};

#endif

