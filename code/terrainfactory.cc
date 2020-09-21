#include "terrainfactory.h"

#include "emptychambertile.h"
#include "horizontalwall.h"
#include "verticalwall.h"
#include "door.h"
#include "passage.h"
#include "stairs.h"

shared_ptr<GameObject> TerrainFactory::spawnObject(int x, int y)
{
    shared_ptr<Terrain> newTerrain;

    switch (type) {
    case '.' :                                  // empty chamber wall
        newTerrain = make_shared<EmptyChamberTile>();
        break;

    case '-' :                                  // horizontal wall
        newTerrain = make_shared<HorizontalWall>();
        break;

    case '|' :                                  // vertical wall
        newTerrain = make_shared<VerticalWall>();
        break;

    case '+' :                                  // door
        newTerrain = make_shared<Door>();

        break;
    case '#' :                                  // passage
        newTerrain = make_shared<Passage>();
        break;

    case '\\' :                                 // stairs
        newTerrain = make_shared<Stairs>();
        break;
    }
    return newTerrain;
}

TerrainFactory::TerrainFactory(char type) : type{ type } {}

void TerrainFactory::setTerrainMade(char newType)
{
    type = newType;
}


