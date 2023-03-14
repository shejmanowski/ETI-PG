#pragma once
#include"Animal.h"

class World;
class Animal;

class Sheep : public Animal {
public:
	Sheep(Position pos, World& world);
};