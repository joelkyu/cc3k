#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class GameObject {
protected:
	bool collision = true;
	char display = '=';
	GameObject(char display) : display{ display } {}

public:

	virtual ~GameObject() {};
	char getDisplay() { return display; }

};

#endif
