#pragma once
#include"Plant.h"

class World;
class Plant;

class Dendelion : public Plant {
public:
	Dendelion(Position pos, World& world);

	void action() override;
};