#pragma once
#include"Animal.h"

class World;
class Animal;

class Antylope : public Animal {
public:
	Antylope(Position pos, World& world);

	void action() override;
};
