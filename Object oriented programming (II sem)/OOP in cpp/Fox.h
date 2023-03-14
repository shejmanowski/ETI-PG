#pragma once
#include"Animal.h"

class World;
class Animal;

class Fox : public Animal {
public:
	Fox(Position pos, World& world);

	void action() override;
};