#pragma once
#include"Organism.h"

class Organism;
class World;

class Plant : public Organism {
public:
	Plant(string name, int strength, char icon, Position pos, World& world);

	void action() override;
	void collision(Organism* other) override;
	void spread();
	void move(Position pos) override;

	~Plant() override;
};