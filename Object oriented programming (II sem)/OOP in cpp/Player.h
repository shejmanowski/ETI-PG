#pragma once
#include"Animal.h"

class World;
class Animal;

class Player : public Animal {
public:
	Player(Position pos, World& world);

	void action() override;
	void collision(Organism* other) override;
};