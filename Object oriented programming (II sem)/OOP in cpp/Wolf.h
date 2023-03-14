#pragma once
#include"Animal.h"

class World;
class Animal;

class Wolf : public Animal {
public:
	Wolf(Position pos, World& world);
};