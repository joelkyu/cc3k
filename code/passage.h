#ifndef PASSAGE_H
#define PASSAGE_H

#include "terrain.h"
class Passage : public Terrain
{
public:
	Passage();
	~Passage() {}
	bool playerCanAccess() override;
	bool enemyCanAccess() override;
};

#endif

