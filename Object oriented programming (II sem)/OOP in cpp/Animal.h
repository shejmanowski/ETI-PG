#pragma once
#include"Organism.h"

class Organism;
class World;

class Animal : public Organism {
public:
	Animal(string name, int strength, int initiative, char icon, Position pos, World& world);
	
	void action() override;
	void collision(Organism* other) override;
	void move(Position pos);
	void reproduce();
	bool isStronger(Organism* other);

	~Animal() override;
};
