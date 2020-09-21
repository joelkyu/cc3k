#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include <iostream>
#include "gameObject.h"

using namespace std;

class Entity : public GameObject {

protected:
	Entity(char display) : GameObject(display) {}

public:
	virtual ~Entity() {}
};

#endif
