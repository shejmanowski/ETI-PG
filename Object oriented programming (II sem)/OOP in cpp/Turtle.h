#pragma once
#pragma once
#include"Animal.h"

class World;
class Animal;

class Turtle : public Animal {
public:
	Turtle(Position pos, World& world);

	void action() override;
	void collision(Organism* other) override;
};